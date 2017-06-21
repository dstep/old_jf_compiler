import re
from collections import defaultdict

class CType:
    def __init__(self, id, var):
        self.id = id
        self.var = var
        self.represent = None
    def unify(self, other):
        me = self.get_repr()
        other = other.get_repr()
        if me == other:
            return
        if me.var and other.var:
            other.represent = me
        elif me.var:
            me.represent = other
        elif other.var:
            other.represent = me
        else:
            if me != other:
                raise RuntimeError("Unable to unify types %s and %s" % (me.id, other.id))
    def __repr__(self):
        return self.get_repr().id
    def get_repr(self):
        if self.represent == None:
            return self
        else:
            return self.represent.get_repr()

TokenType = CType("parsx_token_type", True)
NullType = CType("<null>", False)

class TypeEquation:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

def merge_list(a, b):
    for v in b:
        if v not in a:
            a.append(v)

class Symbol:
    def __init__(self, id, ctype = None):
        self.id = id
        self.rules = []
        self.reset_analysis()
        self.sync = dict()
        self.type = ctype
        self.leaf = None
        self.name = None
        self.expected = []
        self.expected_frozen = False

    def reset_analysis(self):
        self.nullable = False
        self.first = set()
        self.last = set([self])
        self.first_sym = set([self])
        self.follow = set()

    def add_rule(self, rule):
        self.rules.append(rule)

    def get_type(self):
        return self.type

    def solve_nullable(self):
        if self.nullable:
            return False
        for rule in self.rules:
            if rule_nullable(rule):
                self.nullable = True
                return True
        return False

    def solve_first(self):
        first = set()
        first_sym = set([self])
        for rule in self.rules:
            for atom in rule:
                first.update(atom.get_first())
                first_sym.update(atom.get_first_sym())
                if not atom.is_nullable():
                    break
        if first != self.first or first_sym != self.first_sym:
            self.first = first
            self.first_sym = first_sym
            return True
        return False

    def solve_sync(self):
        progress = False
        for rule in self.rules:
            sync = rule_sync(rule)
            for k,v in sync.iteritems():
                if (k not in self.sync) or (v[0] < self.sync[k][0]):
                    self.sync[k] = v
                    progress = True
        return progress

    def solve_expected(self):
        if self.expected_frozen:
            return False
        expected = []
        if self.name <> None:
            expected = set([self.name])
        else:
            for rule in self.rules:
                for atom in rule:
                    merge_list(expected, atom.get_expected())
                    if not atom.is_nullable():
                        break
        if set(self.expected) != set(expected):
            self.expected = expected
            return True
        return False

    def get_expected(self):
        return self.expected

    def init_anchors(self):
        self.anchors = set(self.sync.iterkeys())

    def solve_anchors(self):
        anchors = None
        for rule in self.rules:
            rule_anchors = reduce(lambda s, x : s | (x.get_anchors()), rule, set())
            if anchors == None:
                anchors = rule_anchors
            else:
                anchors = anchors & rule_anchors
        if anchors == None:
            anchors = set()
        if anchors != self.anchors:
            self.anchors = anchors
            return True
        return False

    def update_leaf(self):
        new_leaf = None
        for rule in self.rules:
            rule_leaf = []
            for atom in rule:
                atom_leaf = atom.get_leaf()
                if atom_leaf == None:
                    rule_leaf = None
                    break
                else:
                    rule_leaf.extend(atom_leaf)
            if rule_leaf != None:
                if new_leaf == None:
                    new_leaf = rule_leaf
                elif rule_length(rule_leaf) < rule_length(new_leaf):
                    new_leaf = rule_leaf
        if new_leaf != None and ((self.leaf == None) or (rule_length(self.leaf) > rule_length(new_leaf))):
            self.leaf = new_leaf
            return True
        return False

    def solve_last(self):
        last = set([self])
        for rule in self.rules:
            for atom in reversed(rule):
                last.update(atom.get_last())
                if not atom.is_nullable():
                    break
        if last != self.last:
            self.last = last
            return True
        return False

    def get_leaf(self):
        return self.leaf

    def is_nullable(self):
        return self.nullable

    def get_first(self):
        return self.first

    def get_last(self):
        return self.last

    def get_follow(self):
        return self.follow

    def get_anchors(self):
        return self.anchors

    def get_first_sym(self):
        return self.first_sym

    def get_sync(self):
        return self.sync

    def __repr__(self):
        return self.id

class Action:
    def __init__(self, index, params, ret, code):
        self.index = index
        self.params = params
        self.ret = ret
        self.code = code.strip()
        self.cost = 0
    def is_nullable(self):
        return True
    def get_first(self):
        return set()
    def get_first_sym(self):
        return set()
    def get_last(self):
        return set()
    def get_leaf(self):
        return [self]
    def get_sync(self):
        return dict()
    def get_anchors(self):
        return set()
    def get_expected(self):
        return []
    def get_exact_value(self):
        match = re.match("\$([0-9]+)", self.code)
        if match:
            return int(match.group(1))
        return None
    def __repr__(self):
        return "({0})=>{{{1}}}".format(self.params, self.code)

class Token:
    def __init__(self, name, id = None):
        self.name = name
        self.first = set([self])
        self.sync = dict()
        self.sync[self] = (0, [self])
        self.anchors = set([self])
        self.type = TokenType
        if id == None:
            id = name
        self.id = id
        self.expected = [self]
    def is_nullable(self):
        return False
    def get_first(self):
        return self.first
    def get_first_sym(self):
        return set()
    def get_last(self):
        return set()
    def get_id(self):
        return self.id
    def get_leaf(self):
        return [self]
    def get_sync(self):
        return self.sync
    def get_anchors(self):
        return self.anchors
    def get_expected(self):
        return self.expected
    def get_type(self):
        return self.type
    def __repr__(self):
        return self.name

class RuleSet:
    def __init__(self):
        self.symbols = dict()
        self.actions = dict()
        self.tokens = dict()
        self.sequences = dict()

    def add_token(self, name, id):
        if name in self.symbols:
            raise RuntimeError("Duplicate token definition %s" % name)
        self.tokens[name] = Token(name, id)

    def add_symbol(self, name, type):
        if name in self.symbols:
            raise RuntimeError("Duplicate symbol definition %s" % name)
        self.symbols[name] = Symbol(name, type)

    def get_token(self, name):
        if name not in self.tokens:
            self.tokens[name] = Token(name)
        return self.tokens[name]

    def get_symbol(self, name):
        if name not in self.symbols:
            self.symbols[name] = Symbol(name)
        return self.symbols[name]

    def get_action(self, params, ret, code):
        if (params, ret, code) not in self.actions:
            self.actions[(params, ret, code)] = Action(len(self.actions), params, ret, code)
        return self.actions[(params, ret, code)]

    def add_rule(self, symbol, rule):
        self.get_symbol(symbol).add_rule(rule)

    def solve_nullable(self):
        iterate(lambda : any(map(lambda symbol : symbol.solve_nullable(), self.symbols.itervalues())))
    def solve_first(self):
        iterate(lambda : any(map(lambda symbol : symbol.solve_first(), self.symbols.itervalues())))
        iterate(lambda : any(map(lambda symbol : symbol.solve_last(), self.symbols.itervalues())))
    def solve_leaves(self):
        iterate(lambda : any(map(lambda symbol : symbol.update_leaf(), self.symbols.itervalues())))
        for symbol in self.symbols.itervalues():
            if symbol.get_leaf() == None:
                raise RuntimeError("Symbol %s has no available productions" % symbol.id)
    def solve_sync(self):
        iterate(lambda : any(map(lambda symbol : symbol.solve_sync(), self.symbols.itervalues())))
        map(lambda symbol : symbol.init_anchors(), self.symbols.itervalues())
        iterate(lambda : any(map(lambda symbol : symbol.solve_anchors(), self.symbols.itervalues())))
    def solve_expected(self):
        iterate(lambda : any(map(lambda symbol : symbol.solve_expected(), self.symbols.itervalues())))
        for sym in self.symbols.itervalues():
            sym.expected_frozen = True
    def solve_follow(self):
        def attempt_solve():
            progress = False
            for symbol in self.symbols.itervalues():
                for rule in symbol.rules:
                    symbols = []
                    for atom in rule:
                        first = atom.get_first()
                        for sym in symbols:
                            if len(first - sym.follow) >  0:
                                sym.follow.update(first)
                                progress = True
                        if not atom.is_nullable():
                            symbols = []
                        symbols.extend(atom.get_last())
                    follow = symbol.get_follow()
                    for sym in symbols:
                        if len(follow - sym.follow) >  0:
                            sym.follow.update(follow)
                            progress = True
            return progress
        iterate(attempt_solve)

    def show(self):
        for sym in self.symbols.itervalues():
            print "Symbol {0}".format(sym.id)
            if sym.nullable:
                print " (nullable)"
            for rule in sym.rules:
                print " {0}".format(rule)
            #print "FIRST set: {0}".format(list(sym.first))
            #print "FOLLOW set: {0}".format(list(sym.follow))
            #print "EXPECTED: {0}".format(list(sym.expected))
            #print "ANCHORS: {0}".format(list(sym.anchors))
            #print "SKIP: {0}".format(sym.leaf)
            #print "SYNC set:"
            #for k, v in sym.sync.iteritems():
            #    print "  {0}({1}) => {2}".format(k, v[0], v[1])
            print "\n"

    def typecheck(self):
        for symbol in self.symbols.itervalues():
            if symbol.type.get_repr().var:
                raise RuntimeError("Unable to infer type for symbol %s" % symbol)

    def find_conflicts(self):
        for sym in self.symbols.itervalues():
            if sym.is_nullable() and len(sym.get_first() & sym.get_follow()) > 0:
                intersection = sym.get_first() & sym.get_follow()
                print "FIRST-FOLLOW conflict on {0} : {1}".format(sym, list(intersection))
            first = set()
            conflict = set()
            for rule in sym.rules:
                rf = rule_first(rule)
                conflict.update(first & rf)
                first.update(rf)
                if sym in rule_first_sym(rule):
                    print "LEFT RECURSION on {0} : rule {1}".format(sym, rule)
            if len(conflict) > 0:
                print "FIRST-FIRST conflict on {0} : {1}".format(sym, list(conflict))

    def reset_analysis(self):
        for sym in self.symbols.itervalues():
            sym.reset_analysis()
        self.analysis()

    def analysis(self):
        self.solve_nullable()
        self.solve_first()
        self.solve_follow()

    def refactor_recursion(self):
        new_symbols = []
        replace_rules = []
        for sym in self.symbols.itervalues():
            recursive = False
            for rule in sym.rules:
                if sym in rule_first_sym(rule):
                    recursive = True
            if recursive:
                rec = []
                norec = []
                for rule in sym.rules:
                    (newrec, newnorec) = rule_refactor(rule, [], sym)
                    rec.extend(newrec)
                    norec.extend(newnorec)
                lhs = Symbol(sym.id + "'lhs")
                for rule in norec:
                    lhs.add_rule(rule)
                rhs = Symbol(sym.id + "'rhs")
                for rule in rec:
                    rhs.add_rule(rule + [rhs])
                rhs.add_rule([])
                new_symbols.append(lhs)
                new_symbols.append(rhs)
                replace_rules.append((sym, [lhs, rhs]))
        if len(new_symbols) > 0:
            for sym in new_symbols:
                self.symbols[sym.id] = sym
            for (sym, rule) in replace_rules:
                sym.rules = [rule]
                sym.reset_analysis()
            return True
        return False

    def get_sequence(self, seq):
        if seq not in self.sequences:
            seq_sym = Symbol("(" + str.join("+", map(str, seq)) + ")")
            for index, atom in enumerate(seq):
                if isinstance(atom, Symbol):
                    for rule in atom.rules:
                        if index == len(seq) - 1:
                            seq_sym.rules.append(rule)
                        elif len(rule_first(rule)) != 0:
                            seq_sym.rules.append(rule + list(seq[index + 1:]))
                else:
                    seq_sym.rules.append([atom] + list(seq[index + 1:]))
                merge_list(seq_sym.expected, atom.get_expected())
            seq_sym.expected_frozen = True
            self.symbols[seq_sym.id] = seq_sym
            self.sequences[seq] = seq_sym
        return self.sequences[seq]

    def refactor_sequences(self):
        def work():
            def has_symbol(rule):
                return any(map(lambda t : isinstance(t, Symbol), rule))

            replace_rules = []
            for sym in list(self.symbols.itervalues()):
                new_rules = []
                for rule in sym.rules:
                    new_rule = []
                    seq = []
                    for atom in rule:
                        if atom.is_nullable() and len(atom.get_leaf()) == 0:
                            seq.append(atom)
                        elif len(seq) > 0:
                            if has_symbol(seq):
                                seq.append(atom)
                                new_rule.append(self.get_sequence(tuple(seq)))
                            else:
                                seq.append(atom)
                                new_rule.extend(seq)
                            seq = []
                        else:
                            new_rule.append(atom)
                    if len(seq) > 0:
                        if len(seq) > 1 and has_symbol(seq[:-1]):
                            new_rule.append(self.get_sequence(tuple(seq)))
                        else:
                            new_rule.extend(seq)
                    new_rules.append(new_rule)
                if tuple(sym.rules) != tuple(new_rules):
                    replace_rules.append((sym, new_rules))
            if len(replace_rules) > 0:
                for (sym, rule) in replace_rules:
                    sym.rules = rule
                    sym.reset_analysis()
                self.analysis()
                self.solve_leaves()
                return True
            return False
        iterate(work)


    def refactor_common_factor(self):
        def work():
            replace_rules = []
            new_symbols = []
            for sym in self.symbols.itervalues():
                first = set()
                conflict = set()

                for rule in sym.rules:
                    rf = rule_first(rule)
                    conflict.update(first & rf)
                    first.update(rf)

                if len(conflict) > 0:
                    rules_split = defaultdict(lambda : [])
                    empty_rules = []
                    for rule in sym.rules:
                         if len(rule) > 0:
                            rules_split[rule[0]].append(rule[1:])
                         else:
                            empty_rules.append(rule)
                    if len(rules_split) + len(empty_rules) != len(sym.rules):
                        new_rules = empty_rules
                        for k,v in rules_split.iteritems():
                            if len(v) > 1:
                                new_sym = Symbol(sym.id + "@" + str(k))
                                for rule in v:
                                    new_sym.add_rule(rule)
                                new_rules.append([k, new_sym])
                                new_symbols.append(new_sym)
                            else:
                                new_rules.append([k] + v[0])
                        replace_rules.append((sym, new_rules))
            if len(replace_rules) > 0:
                for sym in new_symbols:
                    self.symbols[sym.id] = sym
                for (sym, rules) in replace_rules:
                    sym.rules = rules
                    sym.reset_analysis()
                self.analysis()
                return True
            return False
        iterate(work)

    def refactor_subst(self):
        def work():
            replace_rules = []
            for sym in self.symbols.itervalues():
                new_rules = []
                progress = False
                for rule in sym.rules:
                    new_rule = []
                    for atom in rule:
                        if isinstance(atom, Symbol) and len(atom.rules) == 1:
                            new_rule.extend(atom.rules[0])
                            progress = True
                        else:
                            new_rule.append(atom)
                    new_rules.append(new_rule)
                if progress:
                    replace_rules.append((sym, new_rules))
            if len(replace_rules) > 0:
                for (sym, rules) in replace_rules:
                    sym.rules = rules
                    sym.reset_analysis()
                self.analysis()
                return True
            return False
        iterate(work)

    def normal_form(self):
        def work():
            replace_rules = []
            for symbol in self.symbols.itervalues():
                all_rules = []
                rules_changed = False
                for rule in symbol.rules:
                    rules = refactor_rule(rule)
                    if rules <> None:
                        rules_changed = True
                        all_rules.extend(rules)
                    else:
                        all_rules.append(rule)
                if rules_changed:
                    replace_rules.append((symbol, all_rules))
            if len(replace_rules) > 0:
                for (sym, rules) in replace_rules:
                    sym.rules = rules
                    sym.reset_analysis()
                self.analysis()
                return True
            return False
        iterate(work)

    def refactor_lfactor(self):
        replace_rules = []
        new_symbols = []
        for sym in self.symbols.itervalues():
            first = set()
            conflict = set()
            for rule in sym.rules:
                rf = rule_first(rule)
                conflict.update(first & rf)
                first.update(rf)
            if len(conflict) > 0:
                new_rules = []
                for rule in sym.rules:
                    rf = rule_first(rule)
                    if len(conflict & rf) > 0:
                        new_rules.extend(rule_refactor_tok(rule, [], conflict))
                    else:
                        new_rules.append(rule)
                rules_split = defaultdict(lambda : [])
                empty_rules = []
                for rule in new_rules:
                    if len(rule) > 0:
                        rules_split[rule[0]].append(rule[1:])
                    else:
                        empty_rules.append(rule)
                new_rules = empty_rules
                for k,v in rules_split.iteritems():
                    if len(v) > 1:
                        new_sym = Symbol(sym.id + "@" + str(k))
                        for rule in v:
                            new_sym.add_rule(rule)
                        new_rules.append([k, new_sym])
                        new_symbols.append(new_sym)
                        if len(new_sym.rules) == 1:
                            raise RuntimeError("generated 1-rule symbol")
                    else:
                        new_rules.append([k] + v[0])
                replace_rules.append((sym, new_rules))
        if len(replace_rules) > 0:
            for sym in new_symbols:
                self.symbols[sym.id] = sym
            for (sym, rules) in replace_rules:
                sym.rules = rules
                sym.reset_analysis()
            self.refactor_common_factor()
            return True
        return False

    def remove_unreachable(self):
        unreachable = []

        def mark(sym):
            if not sym.reachable:
                sym.reachable = True
                for rule in sym.rules:
                    for atom in rule:
                        if isinstance(atom, Symbol):
                            mark(atom)

        for sym in self.symbols.itervalues():
            sym.reachable = False
        for sym in self.symbols.itervalues():
            if not sym.reachable:
                if hasattr(sym, "export") and sym.type.get_repr() != NullType:
                    mark(sym)
        for sym in self.symbols.itervalues():
            if not sym.reachable:
                unreachable.append(sym.id)

        print "Unreachable: %s" % len(unreachable)

        for id in unreachable:
            del self.symbols[id]



def rule_first(rule):
    first = set()
    for atom in rule:
        first.update(atom.get_first())
        if not atom.is_nullable():
            break
    return first

def refactor_rule(rule):
    if len(rule) == 0:
        return None
    if isinstance(rule[0], Symbol):
        new_rules = []
        for symrule in rule[0].rules:
            crule = symrule + rule[1:]
            add_rules = refactor_rule(crule)
            if add_rules:
                new_rules.extend(add_rules)
            else:
                new_rules.append(crule)
        return new_rules
    else:
        return None

def rule_sync(rule):
    sync = dict()
    skipcost = 0
    skippath = []
    for index, atom in enumerate(rule):
        atomsync = atom.get_sync()
        for k, (cost, path) in atomsync.iteritems():
            total_cost = cost + skipcost
            if (k not in sync) or (sync[k][0] > total_cost):
                sync[k] = (total_cost, skippath + path + rule[index + 1:])
        leaf = atom.get_leaf()
        if leaf == None:
            raise RuntimeError("could not skip %s because of %s" % (rule, atom))
        skippath.extend(leaf)
        skipcost = skipcost + rule_length(leaf)
    return sync

def rule_first_sym(rule):
    first_sym = set()
    for atom in rule:
        first_sym.update(atom.get_first_sym())
        if not atom.is_nullable():
            break
    return first_sym

def rule_nullable(rule):
    return all(map(lambda atom : atom.is_nullable(), rule))

def rule_length(rule):
    def atom_length_acc(acc, atom):
        if isinstance(atom, Symbol):
            return acc + rule_length(atom.get_leaf())
        elif isinstance(atom, Token):
            return acc + 1
        else:
            return acc + atom.cost
    return reduce(atom_length_acc, rule, 0)

def rule_refactor_tok(rule, nounfold, conflicts):
    if len(rule) == 0:
        return []
    atom = rule[0]
    if isinstance(atom, Token):
        return [rule]
    elif isinstance(atom, Action):
        return [rule]
    else:
        ans = []
        if atom not in nounfold:
            for unfoldrule in atom.rules:
                ans.extend(rule_refactor_tok(unfoldrule + rule[1:], nounfold, conflicts))
        return ans

def rule_refactor(rule, nounfold, sym):
    if len(rule) == 0:
        return ([], [[]])
    atom = rule[0]
    if isinstance(atom, Token):
        return ([], [rule])
    elif isinstance(atom, Action):
        return ([], [rule])
    else:
        if atom == sym:
            return ([rule[1:]], [])
        elif atom in nounfold:
            return ([], [rule])
        elif sym in atom.get_first_sym():
            rec = []
            norec = []
            for unfoldrule in atom.rules:
                (newrec, newnorec) = rule_refactor(unfoldrule + rule[1:], nounfold + [atom], sym)
                rec.extend(newrec)
                norec.extend(newnorec)
            return (rec, norec)
        else:
            return ([], [rule])

def iterate(fn):
    count = 0
    while fn():
        count = count + 1
        if count > 100:
            raise RuntimeError("No convergence after 1000 iterations")

class TemplateRule:
    def __init__(self, guard, atoms, action):
        self.guard = guard
        self.atoms = atoms
        self.action = action

class Template:
    def __init__(self, id, params):
        self.id = id
        self.params = params
        self.instances = dict()
        self.rules = []
        self.type = CType("@", True)
        self.recovery = None

    def instance(self, params, rs, templates):
        if ( len(params) != len(self.params) ):
            raise RuntimeError("Invalid template instantination for %s" % self.id)
        if ( tuple(params) not in self.instances ):
            print "Instancing %s with %s" % (self.id, params)
            if len(params) == 0:
                sym_name = self.id
            else:
                sym_name = self.id + "(" + str.join(",", map(str, params)) + ")"
            rs.add_symbol(sym_name, self.type)
            sym = rs.get_symbol(sym_name)
            sym.leaf = self.recovery
            self.instances[tuple(params)] = sym
            for rule in self.rules:
                if len(rule.guard) == 0 or eval(rule.guard, dict(zip(self.params, params))):
                    catoms = []
                    ctypes = []
                    for atom in rule.atoms:
                        match = re.match("([^\s\(]+)(:?\s*\((([^\s\),]+)?(:?\s*,\s*([^\s\)]+))*\s*)\))?", atom)
                        if match:
                            atom_name = match.group(1)
                            strparams = match.group(3)
                            cparams = list(map(str.strip, match.group(3).split(","))) if match.group(3) != None else []
                        else:
                            atom_name = atom
                            cparams = []
                        if atom_name in params:
                            atom_name = params[atom_name]
                        if atom_name in templates:
                            evparams = map(lambda param : eval(param, dict(zip(self.params, params))), cparams)
                            catoms.append(templates[atom_name].instance(evparams, rs, templates))
                        else:
                            if len(cparams) > 0:
                                raise RuntimeError("Parametrized token %s encountered" % atom_name)
                            catoms.append(rs.get_token(atom))
                    for catom in catoms:
                        ctypes.append(catom.get_type())
                    act_code = rule.action
                    if act_code == "":
                        if len(catoms) == 1:
                            act_code = "$1"
                        else:
                            self.type.unify(NullType)
                    if len(ctypes) != 1 or act_code.strip() != "$1":
                        action = rs.get_action(tuple(ctypes), self.type, act_code)
                        catoms.append(action)
                        exact_index = action.get_exact_value()
                    else:
                        exact_index = 1
                    if exact_index != None:
                        atom = catoms[exact_index - 1]
                        atom.get_type().unify(self.type)
                    rs.add_rule(sym_name, catoms)
            if re.match("^[a-zA-Z][a-zA-Z0-9_]*$", sym_name):
                sym.export = sym_name
            if hasattr(self, "name"):
                sym.name = self.name
        return self.instances[tuple(params)]

def parse_rule_set(f):
    rs = RuleSet()
    symbols = set()
    rules = []
    state = 0
    types = dict()
    type_binding = dict()
    names = dict()
    types["<null>"] = NullType

    templates = dict()
    template = None

    recovery = dict()

    for line in f.readlines():
        line = line.strip()
        if len(line) == 0:
            continue
        if line[-1] == ":":
            lhs = line.rsplit(":", 1)[0]
            if lhs == "tokens":
                state = 2
            elif lhs == "types":
                state = 3
            elif lhs == "names":
                state = 4
            elif lhs == "recovery":
                state = 5
            else:
                match = re.match("([^\s\(]+)(:?\s*\((([^\s\),]+)?(:?\s*,\s*([^\s\)]+))*\s*)\))?", lhs)
                sym_name = match.group(1)
                params = list(map(str.strip, match.group(3).split(","))) if match.group(3) != None else []
                templates[sym_name] = Template(sym_name, params)
                state = 1
                template = templates[sym_name]
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
            template.rules.append(TemplateRule(guard, map(str.strip, line.split()), action))
        elif state == 5:
            parts = str.split(line, '=>', 1)
            if len(parts) == 2:
                symname = parts[0].strip()
                action = parts[1].strip()
                recovery[symname] = action
            else:
                raise RuntimeError("Invalid recovery definition '%s'" % line)

        elif state == 2:
            parts = str.split(line)
            if len(parts) == 1:
                rs.add_token(parts[0].strip(), parts[0].strip())
            elif len(parts) == 2:
                rs.add_token(parts[0].strip(), parts[1].strip())
            else:
                raise RuntimeError("Invalid token definition '%s'" % line)
        elif state == 3:
            parts = str.split(line, ":", 1)
            if len(parts) == 2:
                sym_names = filter(lambda x : len(x) > 0, map(lambda x : x.strip(), parts[0].split()))
                if len(sym_names) == 0:
                    raise RuntimeError("Invalid type definition '%s'" % line)
                type_name = parts[1].strip()
                if type_name not in types:
                    types[type_name] = CType(type_name, False)
                type = types[type_name]
                for sym in sym_names:
                    if sym == "tokens":
                        TokenType.unify(type)
                    else:
                        type_binding[sym] = type

            else:
                raise RuntimeError("Invalid type definition '%s'" % line)
        elif state == 4:
            parts = str.split(line)
            if len(parts) == 1:
                names[parts[0].strip()] = parts[0].strip()
            elif len(parts) == 2:
                names[parts[0].strip()] = parts[1].strip()
            else:
                raise RuntimeError("Invalid name definition '%s'" % line)

    for sym, act in recovery.iteritems():
        action = rs.get_action((), templates[sym].type, act)
        templates[sym].recovery = [action]
        action.cost = 1

    for sym, name in names.iteritems():
        templates[sym].name = name

    for template in templates.itervalues():
        if len(template.params) == 0:
            template.instance((), rs, templates)
    for type_name in type_binding.iterkeys():
        templates[type_name].type.unify(type_binding[type_name])
    if TokenType.get_repr().var:
        TokenType.unify(CType("parsx_token_type", False))
    rs.typecheck()
    return rs

class Codegen:
    def __init__(self, rs):
        self.rs = rs
        self._indent = ""

    def prepare(self):
        next_state = 1
        next_rule = 1
        for token in self.rs.tokens.itervalues():
            token.state = next_state
            token.rule = next_rule
            next_state = next_state + 1
            next_rule = next_rule + 1
        self.end_token_rule_state = next_rule
        for action in self.rs.actions.itervalues():
            action.state = next_state
            action.rule = next_rule
            next_state = next_state + 1
            next_rule = next_rule + 1
        self.end_action_rule_state = next_rule
        for symbol in self.rs.symbols.itervalues():
            symbol.state = next_state
            symbol.first_rule = next_rule
            next_rule = next_rule + len(symbol.rules)
            next_state = next_state + 1
            sync = dict()
            for k, (cost, rule) in symbol.sync.iteritems():
                if (k in symbol.anchors) or (cost == 0):
                    sync[k] = (cost, rule)
            symbol.sync = sync

    def generate_parser(self, file):
        self.file = file

        def emmit(msg):
            self.file.write(self._indent + msg + "\n")
        def indent():
            self._indent = self._indent + "\t"
        def unindent():
            self._indent = self._indent[:-1]

        for symbol in self.rs.symbols.itervalues():
            if hasattr(symbol, "export") and symbol.type.get_repr() != NullType:
                emmit("parsx_symbol_state(%s, %s, %s)" % (symbol.state, symbol.export, symbol.type))
        emmit("#if defined(parsx_impl)")
        emmit("const parsx_token_id parsx_token_ids[] = {parsx_invalid_token,")
        indent()
        for token in self.rs.tokens.itervalues():
            emmit("parsx_token(%s)," % token.get_id())
        unindent()
        emmit("};")

        rule_positions = dict()
        state_table_length = 1
        emmit("const State parsx_state_table[] = {0,")
        indent()
        for symbol in self.rs.symbols.itervalues():
            line = ""
            for i,rule in enumerate(symbol.rules):
                line = line + "%s," % symbol.state
                state_table_length = state_table_length + 1
                rule_position = (state_table_length, len(rule))
                for atom in rule:
                    line = line + "%s," % atom.state
                state_table_length = state_table_length + len(rule)
                rule_positions[symbol.first_rule + i] = rule_position
            emmit(line)
        unindent()
        emmit("};")
        emmit("const size_t parsx_state_translation[] = {")
        indent()
        maxrule = max(rule_positions.iterkeys()) if len(rule_positions) > 0 else 0
        line = ""
        for i in xrange(maxrule + 1):
            if i in rule_positions:
                line = line + "%s,%s," % rule_positions[i]
            else:
                line = line + "0,0,"
        emmit(line)
        unindent()
        emmit("};")

        emmit("parsx_step_func_begin()")
        indent()
        emmit("while( parsx_has_state ){")
        indent()
        emmit("State parsx_current_state_ = parsx_current_state;")
        emmit("if ( parsx_current_state_ < %s ){" % self.end_token_rule_state)
        indent()
        emmit("if ( parsx_lookahead_token == parsx_token_ids[parsx_current_state_] ){")
        indent()
        emmit("parsx_queue_action(parsx_current_state_);")
        emmit("parsx_pop_state();")
        emmit("parsx_shift_token();")
        emmit("return true;")
        unindent()
        emmit("}else{")
        indent()
        emmit("return false;")
        unindent()
        emmit("}")
        unindent()
        emmit("}else if ( parsx_current_state_ < %s ){" % self.end_action_rule_state)
        indent()
        emmit("parsx_pop_state();")
        emmit("parsx_queue_action(parsx_current_state_);")
        unindent()
        emmit("}else{")
        indent()
        emmit("Action parsx_applied_rule;")
        emmit("switch ( parsx_current_state_ ){")
        for symbol in self.rs.symbols.itervalues():
            emmit("case %s:{ //Symbol %s" % (symbol.state, symbol))
            indent()
            emmit("switch ( parsx_lookahead_token ){")
            indent()
            rule_index = 0
            for rule in symbol.rules:
                first = rule_first(rule)
                if len(first):
                    for token in first:
                        emmit("case parsx_token(%s):parsx_applied_rule = %s;break;" % (token.get_id(), (symbol.first_rule + rule_index)))
                rule_index = rule_index + 1
            null_rule = None
            null_rule_index = 0
            for rule in symbol.rules:
                if rule_nullable(rule):
                    null_rule = rule
                    break
                null_rule_index = null_rule_index + 1
            if null_rule != None:
                emmit("default:parsx_applied_rule = %s;break;" % (symbol.first_rule + null_rule_index))
            else:
                emmit("default:return false;")
            unindent()
            emmit("}")
            unindent()
            emmit("}break;")
        emmit("}")
        emmit("parsx_queue_action(parsx_applied_rule);")
        emmit("parsx_pop_state();")
        emmit("const size_t* parsx_indicies = &parsx_state_translation[parsx_applied_rule * 2];")
        emmit("const State* parsx_states = &parsx_state_table[parsx_indicies[0]];")
        emmit("size_t parsx_push_count = parsx_indicies[1];")
        emmit("while ( parsx_push_count-- ) parsx_push_state(parsx_states[parsx_push_count]);")
        unindent()
        emmit("}")
        unindent()
        emmit("}")
        unindent()
        emmit("parsx_step_func_end()")
        emmit("")
        emmit("")
        emmit("parsx_commit_func_begin()")
        indent()
        emmit("while ( parsx_has_queued_action ){")
        indent()
        emmit("Action parsx_action = parsx_pop_queued_action;")
        emmit("if ( parsx_action < %s ){" % self.end_token_rule_state)
        indent()
        emmit("parsx_commit_token(%s)" % TokenType)
        emmit("return true;")
        unindent()
        emmit("} else if ( parsx_action < %s ){" % self.end_action_rule_state)
        indent()
        emmit("switch ( parsx_action ){")
        for action in self.rs.actions.itervalues():
            emmit("case %s:{ //action %s" % (action.rule, action))
            indent()
            for index, param in reversed(list(enumerate(action.params, 1))):
                if param.get_repr() != NullType:
                    emmit("{0} act_param_{1} = parsx_pop_value({0});".format(param, index))
            code = re.sub("\$([0-9]+)", "act_param_\g<1>", action.code)
            if action.ret.get_repr() == NullType:
                emmit("{0};".format(code))
            else:
                emmit("parsx_push_value({0}, {1});".format(action.ret, code))
            unindent()
            emmit("}break;")
        unindent()
        emmit("}")
        unindent()
        emmit("}")
        unindent()
        emmit("}")
        emmit("return false;")
        unindent()
        emmit("parsx_commit_func_end()")
        emmit("")
        emmit("")
        emmit("parsx_undo_func_begin()")
        indent()
        emmit("while ( parsx_has_queued_action ){")
        indent()
        emmit("Action parsx_action = parsx_pop_last_queued_action;")
        emmit("if ( parsx_action < %s ){" % self.end_token_rule_state)
        indent()
        emmit("parsx_unshift_token();")
        emmit("parsx_push_state(parsx_action);")
        unindent()
        emmit("} else if ( parsx_action < %s ){" % self.end_action_rule_state)
        indent()
        emmit("parsx_push_state(parsx_action);")
        unindent()
        emmit("} else {")
        indent()
        emmit("const size_t* parsx_indicies = &parsx_state_translation[parsx_action * 2];")
        emmit("size_t parsx_pop_count = parsx_indicies[1];")
        emmit("while ( parsx_pop_count-- ) parsx_pop_state();")
        emmit("parsx_push_state(parsx_state_table[parsx_indicies[0] - 1]);")
        unindent()
        emmit("}")
        unindent()
        emmit("}")
        unindent()
        emmit("parsx_undo_func_end()")

        skips = dict()
        sync = dict()
        expects = dict()
        expects_table = []

        for token in self.rs.tokens.itervalues():
            skips[token.state] = token.get_leaf()
            sync[token.state] = token.get_sync()
            expects_table.append(token)
        for symbol in self.rs.symbols.itervalues():
            skips[symbol.state] = symbol.get_leaf()
            sync[symbol.state] = symbol.get_sync()
            expected = symbol.get_expected()
            if len(expected) > 0:
                expects[symbol.state] = (len(expects_table), expected)
                expects_table.extend(list(expected))
        for action in self.rs.actions.itervalues():
            if hasattr(action, "recovery"):
                skips[action.state] = [action.recovery]
            else:
                skips[action.state] = action.get_leaf()
            sync[action.state] = action.get_sync()

        emmit("")
        emmit("")
        emmit("parsx_sync_mask_table_begin()")
        indent()
        maxstate = max(sync.iterkeys()) if len(sync) > 0 else 0
        for i in xrange(maxstate + 1):
            if i in sync:
                keys = list(sync[i].iterkeys())
                emmit("parsx_sync_mask(%s)" % str.join(", ", [str(len(keys))] + map(lambda k : "parsx_token(%s)" % k.get_id(), keys)))
            else:
                emmit("parsx_sync_mask(0)")
        unindent()
        emmit("parsx_sync_mask_table_end()")
        emmit("")
        emmit("")
        emmit("parsx_sync_cost_func_begin()")
        indent()
        emmit("switch ( parsx_sync_state ){")
        indent()
        for k, v in sync.iteritems():
            emmit("case %s:{" % (k))
            indent()
            emmit("switch ( parsx_sync_token ){")
            indent()
            for tok, rule in v.iteritems():
                emmit("case parsx_token(%s):{return %s;}break;" % (tok.get_id(), rule[0]))
            emmit("default:{return %s;}break;" % (rule_length(skips[k])))
            unindent()
            emmit("}")
            unindent()
            emmit("}break;")
        unindent()
        emmit("}")
        unindent()
        emmit("parsx_sync_cost_func_end()")
        emmit("")
        emmit("")
        emmit("parsx_sync_func_begin()")
        indent()
        emmit("switch ( parsx_current_state ){")
        indent()
        for k, v in sync.iteritems():
            emmit("case %s:{" % (k))
            indent()
            emmit("switch ( parsx_lookahead_token ){")
            indent()
            for tok, rule in v.iteritems():
                emmit("case parsx_token(%s):{" % (tok.get_id()))
                indent()
                emmit("parsx_pop_state();")
                for index, atom in enumerate(rule[1]):
                    if atom == tok:
                        for atom in reversed(rule[1][index:]):
                            emmit("parsx_push_state(%s);" % atom.state)
                        break
                    else:
                        if isinstance(atom, Token):
                            emmit("parsx_insert_token(%s);" % atom.get_id())
                            emmit("parsx_queue_action(%s);" % atom.rule)
                        elif isinstance(atom, Action):
                            emmit("parsx_queue_action(%s);" % atom.rule)
                unindent()
                emmit("}break;")
            emmit("default:{")
            indent()
            emmit("parsx_pop_state();")
            for atom in skips[k]:
                if isinstance(atom, Token):
                    emmit("parsx_insert_token(%s);" % atom.get_id())
                    emmit("parsx_queue_action(%s);" % atom.rule)
                elif isinstance(atom, Action):
                    emmit("parsx_queue_action(%s);" % atom.rule)
            unindent()
            emmit("}break;")
            unindent()
            emmit("}")
            unindent()
            emmit("}break;")
        unindent()
        emmit("}")
        unindent()
        emmit("parsx_sync_func_end()")
        emmit("")
        emmit("")
        emmit("size_t parsx_expect_translation[] = {")
        line = ""
        for i in xrange(maxstate + 1):
            if i in expects:
                line = line + "%s," % expects[i][0]
            else:
                line = line + "0,"
        emmit(line)
        emmit("};")
        emmit("size_t parsx_expect_translation_n[] = {")
        line = ""
        for i in xrange(maxstate + 1):
            if i in expects:
                line = line + "%s," % len(expects[i][1])
            else:
                line = line + "0,"
        emmit(line)
        emmit("};")
        emmit("parsx_expect_type parsx_expect_table[] = {")
        line = ""
        for e in expects_table:
            if isinstance(e, Token):
                line = line + ("parsx_expect_token(%s)," % e.get_id())
            else:
                line = line + ("parsx_expect_value(%s)," % e)
        emmit(line)
        emmit("};")
        emmit("parsx_expected_func_begin()")
        indent()
        emmit("State parsx_expect_state_ = parsx_expect_state;")
        emmit("if ( parsx_expect_state_ < %s ){" % self.end_token_rule_state)
        indent()
        emmit("parsx_expect(parsx_expect_table[parsx_expect_state_ - 1]);")
        unindent()
        emmit("} else if ( parsx_expect_state_ >= %s ){" % self.end_action_rule_state)
        indent()
        emmit("parsx_expect_type* expect_id = &parsx_expect_table[parsx_expect_translation[parsx_expect_state_]];")
        emmit("size_t parsx_n_expects = parsx_expect_translation_n[parsx_expect_state_];")
        emmit("while ( parsx_n_expects-- ){ parsx_expect(*expect_id); expect_id++; }")
        unindent()
        emmit("}")
        unindent()
        emmit("parsx_expected_func_end()")
        emmit("#endif")

import sys
if len(sys.argv) >= 2:
    inputFile = sys.argv[1]
    outputFile = sys.argv[2]
else:
    inputFile = "grammar.txt"
    outputFile = "D:/Dropbox/etc/parserexample/parserexample/src/parser_core.inc"

rs = parse_rule_set(open(inputFile, "r"))
rs.show()

rs.analysis()

print "Analyze done\n"
rs.find_conflicts()
print "Refactoring\n"

rs.refactor_common_factor()

while rs.refactor_recursion():
    rs.analysis()

while  rs.refactor_lfactor():
    rs.analysis()


rs.solve_expected()
rs.solve_leaves()
rs.normal_form()
rs.refactor_sequences()
rs.solve_expected()

rs.refactor_subst()

rs.reset_analysis()

print "Refactoring done\n"
print "======================\n"
rs.solve_leaves()
rs.solve_sync()

rs.remove_unreachable()

rs.show()
rs.find_conflicts()

codegen = Codegen(rs)
codegen.prepare()

with open(outputFile, "w") as f:
    codegen.generate_parser(f)