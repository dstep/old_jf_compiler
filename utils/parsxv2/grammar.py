import typesystem
import warnings
import graphviz
from collections import defaultdict

class Atom(object):
    def __init__(self):
        super(Atom, self).__init__()
        self.sync = dict()
        self.expects = set()

    def get_nullable(self):
        return None

    def get_sync(self):
        return self.sync

    def __repr__(self):
        return self.name

class ExpectedName:
    def __init__(self, name):
        self.name = name
    def __hash__(self):
        return hash(self.name)
    def __eq__(self, other):
        return self.name == other.name
    def __repr__(self):
        return self.name

class Rule:
    def __init__(self, id, sequence):
        self.id = id
        self.sequence = sequence

    def is_nullable(self):
        def reducer(seq, atom):
            if seq == None:
                return None
            atom_seq = atom.get_nullable()
            if atom_seq == None:
                return None
            return seq + atom_seq
        return reduce(reducer, self.sequence, [])

def get_rule_ids(rule):
    ids = defaultdict(lambda : 0)
    for atom in rule:
        if isinstance(atom, RuleIdentity):
            ids[atom] = ids[atom] + 1
    return ids

class GraphNode(object):
    def __init__(self):
        super(GraphNode, self).__init__()
        self.inedges = []
        self.outedges = []
        self.outpaths = []
        self.inpaths = []
        self.marked = False
        self.name = "empty"
        self.accessible = set()
        self.ancestors = set()
        self.graph = None
        self.processed = False

    def is_empty_node(self):
        return False

    def add_to_graph(self, graph):
        self.graph = graph
        self.add_node(graph)
        for edge in self.inedges:
            self.add_edge_to_graph(edge, self.graph)

    def add_edge_to_graph(self, edge, graph):
        label = "" #str(list(get_rule_ids(edge.rule).iterkeys()))
        graph.edge(str(edge.outv), str(edge.inv), label)

    def add_node(self, graph):
        graph.node(str(self), str(self))

    def __repr__(self):
        return self.name

    def make_edges(self):
        for rule in self.rules:
            lhs = []
            for (index,atom) in enumerate(rule):
                if isinstance(atom, GraphNode):
                    edge = Edge(atom, self, lhs + rule[index:])
                    self.inedges.append(edge)
                    if self.graph != None:
                        self.add_edge_to_graph(edge, self.graph)
                    atom.outedges.append(edge)
                nullable = atom.get_nullable()
                if nullable == None:
                    lhs = None
                    break
                lhs.extend(nullable)


class EmptyGraphNode(GraphNode):
    def __init__(self):
        super(EmptyGraphNode, self).__init__()

    def is_empty_node(self):
        return True

EmptyNode = EmptyGraphNode()

class Terminal(Atom,GraphNode):
    def __init__(self, name):
        super(Terminal, self).__init__()
        self.name = name
        self.type = typesystem.TypeVar(self.name)
        self.sync = dict([(self, (0, [self])), (None, (1, [self]))])
        self.expects = set([self])
        self.processed = True

    def add_node(self, graph):
        graph.node(str(self), str(self), fillcolor="turquoise", style="filled")

    def get_id(self):
        if hasattr(self, "id"):
            return self.id
        return self.name


class LoopPath(Atom,GraphNode):
    def __init__(self, node):
        super(LoopPath, self).__init__()
        self.node = node
        self.sync = dict()
        self.name = "%s loop" % (self.node)
        self.processed = False
    def add_node(self, graph):
        graph.node(str(self), str(self), fillcolor="coral", style="filled")

    def do_work(self, grammar):
        paths = []
        for edge in self.node.outedges:
            if edge.inv == self.node:
                paths.append(path_extend(([], [], self.node), (edge.rule, self.node)))
            elif self.node in edge.inv.accessible:
                prepath = path_extend(([], [], self.node), (edge.rule, edge.inv))
                path = find_path(grammar, edge.inv, self.node)
                paths.append(paths_concat(prepath, path))

        self.rules = []
        for (lhs,rhs,prod) in paths:
            if len(lhs) > 0:
                warnings.warn("Loop action %s ignored" % rhs)
            else:
                self.rules.append(rhs + [self])
        self.rules.append([])
        self.nullable = []

    def get_nullable(self):
        return self.nullable


class SplitPath(Atom,GraphNode):
    def __init__(self, start, end):
        super(SplitPath, self).__init__()
        self.name = "(%s->%s)" % (start, end)
        self.start = start
        self.sync = dict()
        self.end = end
        self.nullable = None


    def add_node(self, graph):
        graph.node(str(self), str(self), fillcolor="pink", style="filled")

    def do_work(self, grammar):
        paths = []
        for edge in self.start.outedges:
            if (self.end in edge.inv.accessible or self.end == edge.inv) and (edge.inv != self.start):
                path = find_path(grammar, edge.inv, self.end)
                if not edge.inv.processed:
                    raise RuntimeError("Attempting to process node while dependencies are not processed")
                rhs = [grammar.get_loop(edge.inv)] if edge.inv in edge.inv.accessible else []
                prepath = path_extend(([], [], self.start), (edge.rule + rhs, edge.inv))
                paths.append(paths_concat(prepath, path))

        self.rules = []
        for (lhs,rhs,prod) in paths:
            if len(lhs)> 0:
                warnings.warn("Split action %s ignored (while processing %s)" % ((lhs, rhs), self))
            else:
                ids = get_rule_ids(rhs)
                if any(map(lambda k : k > 1, ids.itervalues())):
                    warnings.warn("Split action %s ignored (rule repetition) (while processing %s)" % (rhs, self))
                else:
                    self.rules.append(rhs)

    def get_nullable(self):
        return self.nullable

class NonTerminal(Atom, GraphNode):
    def __init__(self, name, expected_name):
        super(NonTerminal, self).__init__()
        self.sync = dict()
        self.name = name
        self.type = typesystem.TypeVar(self.name)
        self.nullable = None
        self.rules = []
        self.processed = False
        if expected_name != None:
            self.expects = frozenset([expected_name])

    def add_node(self, graph):
        graph.node(str(self), str(self), fillcolor="lawngreen", style="filled")

    def add_rule(self, id, rule, action):
        total_rule = rule + [action, id]
        self.rules.append(total_rule)

    def get_nullable(self):
        return self.nullable

class Edge:
    def __init__(self, outv, inv, rule):
        self.outv = outv
        self.inv = inv
        self.rule = rule

class RuleIdentity(Atom):
    def __init__(self, text):
        super(RuleIdentity, self).__init__()
        self.text = text
        self.sync = dict([(None, (0, []))])
        self.processed = True
    def get_nullable(self):
        return [self]
    def __repr__(self):
        return "(%s)" % self.text
    def instance(self):
        return RuleIdentity(self.text)

class Action(Atom):
    def __init__(self, type, code):
        super(Action, self).__init__()
        self.type = type
        self.code = code
        self.sync = dict([(None, (0, [self]))])
        self.processed = True

    def get_nullable(self):
        return [self]
    def __repr__(self):
        return "(%s){" % (self.type) + self.code + "}"

class Grammar:
    def __init__(self):
        self.terminals = dict()
        self.non_terminals = []
        self.loops = dict()
        self.splits = dict()
        self.worklist = []
        self.graph = graphviz.Digraph(engine="dot")

    def add_nt(self, nt):
        self.non_terminals.append(nt)
        nt.add_to_graph(self.graph)

    def get_terminal(self, name):
        if name not in self.terminals:
            terminal = Terminal(name)
            self.terminals[name] = terminal
            terminal.add_to_graph(self.graph)
        return self.terminals[name]

    def get_split(self, start, end):
        if (start,end) not in self.splits:
            splitPath = SplitPath(start, end)
            self.splits[(start,end)] = splitPath
            self.worklist.append(splitPath)
            splitPath.add_to_graph(self.graph)
        return self.splits[(start,end)]

    def get_loop(self, node):
        if node not in self.loops:
            loopPath = LoopPath(node)
            self.loops[node] = loopPath
            self.worklist.append(loopPath)
            loopPath.add_to_graph(self.graph)
        return self.loops[node]

    def do_work(self):
        def iterate_local(fn, list):
            while any(map(fn, list)):
                pass

        worklist = []
        while len(self.worklist) > 0:
            newlist = self.worklist
            worklist.extend(newlist)
            self.worklist = []

            for atom in newlist:
                atom.do_work(self)

        iterate_local(update_nullable, worklist)

        for atom in worklist:
            atom.make_edges()
        for atom in worklist:
            find_transitive_closure(atom)

        iterate_local(update_sync, worklist)
        iterate_local(update_expected, worklist)


    def iterate(self, fn):
        while any(map(fn, self.non_terminals)):
            pass

    def make_edges(self):
        for nt in self.non_terminals:
            nt.make_edges()

def compare_sync(sync1, sync2):
    if len(sync1) != len(sync2):
        return False
    for k,(cost,rule) in sync1.iteritems():
        if k not in sync2:
            return False
        if sync2[k][0] != cost:
            return False
    return True

def eval_nullable(nt):
    nullables = map(lambda rule : Rule(None, rule).is_nullable(), nt.rules)
    for nullable in nullables:
        if nullable != None:
            return nullable
    return None

def rule_expected(rule):
    expected = set()
    for atom in rule:
        expected.update(atom.expects)
        if atom.get_nullable() == None:
            break
    return expected

def eval_expected(nt):
    if isinstance(nt.expects, frozenset):
        return nt.expects
    return reduce(lambda s, rule : s.union(rule_expected(rule)), nt.rules, set())

def update_expected(nt):
    expected = eval_expected(nt)
    if expected != nt.expects:
        nt.expects = expected
        return True
    return False

def eval_sync_set(nt):
    sync = dict()
    for rule in nt.rules:
        skip_rule = []
        skip_cost = 0
        for index, atom in enumerate(rule):
            atom_sync = atom.get_sync()
            for (term,(cost,syncrule)) in atom_sync.iteritems():
                if term != None and (term not in sync or skip_cost + cost < sync[term][0]):
                    sync[term] = (skip_cost + cost, skip_rule + syncrule + rule[index + 1:])
            if None in atom_sync:
                skip_cost = skip_cost + atom_sync[None][0]
                skip_rule.extend(atom_sync[None][1])
            else:
                skip_rule = None
                break
        if skip_rule <> None:
            if None not in sync or sync[None][0] > skip_cost:
                sync[None] = (skip_cost, skip_rule)
    return sync

def update_sync(nt):
    sync = eval_sync_set(nt)
    if not compare_sync(sync, nt.sync):
        nt.sync = sync
        return True
    return False

def update_nullable(nt):
    if nt.get_nullable() == None:
        nt.nullable = eval_nullable(nt)
        if nt.nullable != None:
            return True
    return False

def find_transitive_closure(nt):
    def visit_dfs(root, atom):
        for edge in atom.inedges:
            if edge.outv not in root.ancestors:
                root.ancestors.add(edge.outv)
                edge.outv.accessible.add(root)
                visit_dfs(root, edge.outv)
    visit_dfs(nt, nt)
    nt.processed = True


class DominatorSet:
    def __init__(self, start, end):
        all_set = set()

        def find_nodes(all_set, v):
            if v not in all_set:
                all_set.add(v)
                for ov in v.accessible:
                    if end in ov.accessible or end == ov:
                        find_nodes(all_set, ov)

        find_nodes(all_set, start)
        doms = dict()
        doms[start] = set([start])
        for v in all_set:
            if v != start:
                doms[v] = all_set.copy()
        changes = True
        while changes:
            changes = False
            for v in all_set:
                if v != start:
                    new_set = all_set.copy()
                    for edge in v.inedges:
                        iv = edge.outv
                        if iv in all_set:
                            new_set.intersection_update(doms[iv])
                    new_set.add(v)
                    if new_set != doms[v]:
                        changes = True
                        doms[v] = new_set
        self.doms = doms

        self.idoms = dict()
        for v in all_set:
            for dom in self.doms[v]:
                if dom != v:
                    idom = True
                    for dom1 in self.doms[v]:
                        if dom1 != v and self.is_sdom(dom, dom1):
                            idom = False
                    if idom:
                        self.idoms[v] = dom


    def is_dom(self, start, end):
        return start in self.doms[end]

    def is_sdom(self, start, end):
        return start in self.doms[end] and start != end

    def get_idom(self, node):
        return self.idoms[node] if node in self.idoms else None

    def get_dominators(self, node):
        return self.doms[node]

def path_extend(path, rule_prod):
    (lhs, rhs, root) = path
    (rule, prod) = rule_prod
    if root.is_empty_node():
        rule_lhs = []
        rule_rhs = rule[:]
    else:
        pos = rule.index(root)
        rule_lhs = filter(lambda t : not isinstance(t, RuleIdentity), rule[:pos])
        rule_rhs = rule[pos+1:]
    root = prod
    lhs = rule_lhs + lhs
    rhs = rhs + rule_rhs
    return (lhs, rhs, root)

def paths_concat(l, r):
    (llhs, lrhs, lroot) = l
    (rlhs, rrhs, rroot) = r
    return (rlhs + llhs, lrhs + rrhs, rroot)

def find_path(grammar, start, end):
    seq = []
    dom = DominatorSet(start, end)
    cur = end
    while cur != start:
        idom = dom.get_idom(cur)
        edges = []
        for edge in idom.outedges:
            if edge.inv != idom and (edge.inv == cur or cur in edge.inv.accessible):
                edges.append(edge)
        if len(edges) == 1:
            rule = []
            rule.extend(edges[0].rule)
            if cur in cur.accessible:
                rule.append(grammar.get_loop(cur))
            seq.append((rule, cur))
        else:
            if idom.is_empty_node():
                seq.append(([grammar.get_split(idom, cur)], cur))
            else:
                seq.append(([idom, grammar.get_split(idom, cur)], cur))
        cur = idom
    seq.reverse()
    path = reduce(path_extend, seq, ([], [], start))
    return path

