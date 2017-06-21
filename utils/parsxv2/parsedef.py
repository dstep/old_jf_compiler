from grammar import *
from typesystem import *
import warnings
import re

class NTTemplate:
    def __init__(self, name, params):
        self.name = name
        self.productions = []
        self.type = None
        self.params = tuple(params)
        self.expected_name = None
        self.instances = dict()

    def add_production(self, prod):
        self.productions.append(prod)

    def instance(self, grammar, non_terminals, args, g_non_terminals):
        args = tuple(args)
        if args in self.instances:
            return self.instances[args]
        if len(args) != len(self.params):
            raise RuntimeError("Invalid instantination of %s with parameters (%s)" % (self.name, args))
        name = self.name
        if len(args) > 0:
            name = name + "(" + str.join(", ", map(str, args)) + ")"
        print "Instantiation for %s" % name
        nt = NonTerminal(name, self.expected_name)
        if self.type != None:
            nt.type = self.type
        g_non_terminals.append(nt)
        if re.match("^[a-zA-Z][a-zA-Z0-9_]*$", name):
            nt.export = name
        self.instances[args] = nt
        arg_dict = dict(zip(self.params, args))
        for (ruleid,guard,symbols,action) in self.productions:
            if len(guard) > 0:
                if not eval(guard, arg_dict):
                    continue
            atoms = []
            for symbol in symbols:
                match = re.match("([^\s(]+)\s*[(](.*)[)]$", symbol)
                if match:
                    symbol_name = match.group(1)
                    strparams = match.group(2)
                    params = re.findall("[^,']+|'[^']+'", strparams)
                    symbol_params = map(lambda s : str.strip(s, " '"), params)
                    symbol_params = map(lambda t:eval(t, arg_dict), symbol_params)
                else:
                    symbol_name = symbol
                    symbol_params = []
                if symbol_name in non_terminals:
                    template = non_terminals[symbol_name]
                    atoms.append(template.instance(grammar, non_terminals, symbol_params, g_non_terminals))
                else:
                    if len(symbol_params) > 0:
                        raise RuntimeError("Parameters given for terminal %s" % symbol_name)
                    atoms.append(grammar.get_terminal(symbol_name))
            exact_index = None
            if len(action) == 0 and len(atoms) == 1:
                exact_index = 0
                action = "$1"
            else:
                match = re.match("^\$([0-9]+)$", action)
                if match:
                    exact_index = int(match.group(1)) - 1
            types = map(lambda atom : atom.type, atoms)
            if exact_index != None:
                types_unify(nt.type, types[exact_index])
            type = nt.type
            for atom_type in types:
                type = TypeArrow(atom_type, type)
            action = Action(type, action)
            nt.add_rule(ruleid.instance(), atoms, action)
        return nt

def parse_grammar(file):
    g = Grammar()

    nt = None
    non_terminals = dict()
    types = dict()
    nt_types = dict()
    productions = dict()
    state = 0
    names = dict()

    types["<null>"] = TypeTuple(())

    line_index = 0

    for line in file.readlines():
        line_index = line_index + 1
        line = line.strip()
        if len(line) == 0:
            continue
        if line[-1] == ":":
            lhs = line.rsplit(":", 1)[0].strip()
            if lhs == "types":
                state = 2
            elif lhs == "tokens":
                state = 3
            elif lhs == "names":
                state = 4
            else:
                match = re.match("([^\s\(]+)(:?\s*\((([^\s\),]+)?(:?\s*,\s*([^\s\)]+))*\s*)\))?", lhs)
                nt = match.group(1)
                params = list(map(str.strip, match.group(3).split(","))) if match.group(3) != None else []
                state = 1
                nt = nt.strip()
                if nt not in non_terminals:
                    non_terminals[nt] = NTTemplate(nt,params)
                    state = 1
                else:
                    warnings.warn("Second definition for %s ignored." % nt)
                    state = 0
        elif state == 1:
            parts = str.split(line, '|', 1)
            if len(parts) == 2:
                guard = parts[0].strip()
                line = parts[1].strip()
            else:
                guard = ""
            parts = str.rsplit(line, '=>', 1)
            if len(parts) == 2:
                action = parts[1].strip()
                line = parts[0].strip()
            else:
                action = ""
            if line == "<e>":
                line = ""
            non_terminals[nt].add_production((RuleIdentity("rule at %s" % line_index), guard, map(str.strip, line.split()), action))
        elif state == 2:
            parts = str.split(line, ":", 1)
            if len(parts) == 2:
                sym_names = filter(lambda x : len(x) > 0, map(lambda x : x.strip(), parts[0].split()))
                if len(sym_names) == 0:
                    raise RuntimeError("Invalid type definition '%s'" % line)
                type_name = parts[1].strip()
                if type_name not in types:
                    types[type_name] = TypeConstant(type_name)
                for sym in sym_names:
                    nt_types[sym] = types[type_name]
            else:
                warnings.warn("Invalid type definition '%s'" % line)
        elif state == 3:
            parts = str.split(line)
            if len(parts) != 2:
                raise RuntimeError("Invalid token definition '%s'" % line)
            g.get_terminal(parts[0].strip()).id = parts[1].strip()
        elif state == 4:
            parts = str.split(line, ":", 1)
            if len(parts) == 2:
                sym_names = filter(lambda x : len(x) > 0, map(lambda x : x.strip(), parts[0].split()))
                if len(sym_names) == 0:
                    raise RuntimeError("Invalid name definition '%s'" % line)
                name = parts[1].strip()
                for sym in sym_names:
                    names[sym] = name
            else:
                warnings.warn("Invalid name definition '%s'" % line)

    for (symbol, name) in names.iteritems():
        if symbol not in non_terminals:
            warnings.warn("Name declarartion for non-terminal %s." % symbol)
        else:
            non_terminals[symbol].expected_name = ExpectedName(name)

    for (nt, t) in nt_types.iteritems():
        if nt not in non_terminals:
            warnings.warn("Type given for %s doesn't have any productions. Ignored." % nt)
        else:
            non_terminals[nt].type = t

    g_non_terminals = []
    for template in non_terminals.itervalues():
        if len(template.params) == 0:
            template.instance(g, non_terminals, [], g_non_terminals)

    token_type = TypeConstant("parsx_token_type")

    for terminal in g.terminals.itervalues():
        types_unify(terminal.type, token_type)

    for nt in g_non_terminals:
        if not isinstance(nt.type.get_repr(), TypeConstant) and not (isinstance(nt.type.get_repr(), TypeTuple) and len(nt.type.get_repr().args) == 0):
            raise RuntimeError("Unable to infer type for %s" % nt)

    for nt in g_non_terminals:
        def drop_unused_actions(nt, rule):
            seq_type = infer_type_from_sequence(map(lambda t:t.type if hasattr(t, "type") else TypeTuple(()), rule))
            types_unify(nt.type, seq_type)
            action = rule[-2]
            action_type = infer_type_from_sequence([action.type])
            match = re.match("^\$([0-9]+)$", action.code)
            if match:
                if is_simple_arrow(action_type):
                    rule.remove(action)
        for rule in nt.rules:
            drop_unused_actions(nt, rule)

    disjoint = set()
    for nt1 in g_non_terminals:
        for nt2 in g_non_terminals:
            if nt1.expects != nt2.expects:
                disjoint.add((nt1,nt2))
            if not types_equal(nt1.type, nt2.type):
                disjoint.add((nt1,nt2))
            if hasattr(nt1, "export") and hasattr(nt2, "export") and nt1.export != nt2.export:
                disjoint.add((nt1,nt2))
            if len(nt1.rules) <> len(nt2.rules):
                disjoint.add((nt1,nt2))

    progress = True
    while progress:
        progress = False
        for nt1 in g_non_terminals:
            for nt2 in g_non_terminals:
                if (nt1,nt2) not in disjoint:
                    for (rule1,rule2) in zip(nt1.rules, nt2.rules):
                        if len(rule1) != len(rule2):
                            disjoint.add((nt1,nt2))
                            progress = True
                        else:
                            similar = True
                            for (a1,a2) in zip(rule1, rule2):
                                if type(a1) != type(a2):
                                    similar = False
                                    break
                                if a1 == a2:
                                    continue
                                if isinstance(a1, RuleIdentity):
                                    continue
                                if isinstance(a1, NonTerminal) and (a1,a2) in disjoint:
                                    similar = False
                                    break
                                if isinstance(a1, Action) and (not types_equal(a1.type, a2.type) or a1.code != a2.code):
                                    similar = False
                                    break
                            if not similar:
                                if nt1 == nt2:
                                    pass
                                disjoint.add((nt1,nt2))
                                progress = True

    representatives = dict()
    filter_nts = set()
    for nt1 in g_non_terminals:
        for nt2 in g_non_terminals:
            if (nt1,nt2) not in disjoint:
                if nt1 != nt2:
                    filter_nts.add(nt1)
                representatives[nt1] = nt2
                break

    for nt in g_non_terminals:
        for rule in nt.rules:
            for index, atom in enumerate(rule):
                if atom in representatives:
                    rule[index] = representatives[atom]

    g_non_terminals = filter(lambda nt : nt not in filter_nts, g_non_terminals)
    for nt in g_non_terminals:
        g.add_nt(nt)

    return g

import sys
if len(sys.argv) >= 2:
    inputFile = sys.argv[1]
    outputFile = sys.argv[2]
    show_graph = False
else:
    inputFile = "g1.txt"
    outputFile = "D:/Dropbox/etc/parserexample/parserexample/src/parser_core.inc"
    show_graph = True

g = parse_grammar(open(inputFile, "r"))
g.iterate(update_nullable)
g.iterate(update_sync)
g.iterate(update_expected)
g.make_edges()

nodes = []
for nt in g.non_terminals:
    nodes.append(nt)
for t in g.terminals.itervalues():
    nodes.append(t)
nodes.append(EmptyNode)
map(find_transitive_closure, nodes)

def figure_state(nt):
    nt.transitions = dict()
    for t in nt.ancestors:
        if isinstance(t, Terminal):
            (lhs, rhs, prod) = find_path(g, t, nt)
            nt.transitions[t] = lhs + [t] + rhs
    if nt.get_nullable() != None:
        nt.transitions[None] = nt.get_nullable()

for nt in g.non_terminals:
    figure_state(nt)
g.do_work()
visited = set()

progress = True
while progress:
    progress = False
    worklist = list(g.splits.itervalues()) + list(g.loops.itervalues())
    for node in worklist:
        if node not in visited:
            visited.add(node)
            figure_state(node)
            progress = True
    g.do_work()


import codegen

with open(outputFile, "w") as file:
    stream = codegen.Stream(file)
    code = codegen.Codegen(g)
    code.codegen(stream)

if show_graph:
    g.graph.view()


