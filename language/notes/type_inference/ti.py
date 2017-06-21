import graphviz


def unique_var_names():
    i = 0
    while True:
        yield "v{0}".format(i)
        i = i + 1

unique_var = unique_var_names()


class TypeNode(object):
    def __init__(self):
        self.inedges = []
        self.outedges = []

    def get_repr(self):
        return self

    def add_inedge(self, edge):
        self.inedges.append(edge)
    def add_outedge(self, edge):
        self.outedges.append(edge)

    def get_label(self):
        return self.name

    def update_upper_bound(self, subtyping):
        return False

    def do_update_upper_bound(self, subtyping, new_upper_bound):
        return False

    def make_node(self, graph):
        pass

    def __repr__(self):
        return self.name

class TypeClass(TypeNode):
    def __init__(self, name, bases):
        super(TypeClass, self).__init__()
        self.name = name
        self.bases = bases
        self.all_bases = set(bases)
        self.methods = dict()
        for base in self.bases:
            self.all_bases.update(base.all_bases)
            for method in base.methods.itervalues():
                self.methods[method.name] = method

    def add_method(self, name, params, ret):
        self.methods[name] = Method(name, params, ret)

    def get_upper_bound(self):
        return (self,)

    def make_node(self, graph):
        graph.node(self.name, self.get_label(), fillcolor="tomato", style="filled")


class Method:
    def __init__(self, name, params, ret):
        self.params = params
        self.ret = ret
        self.name = name

class MethodCallConstraint:
    def __init__(self, usage, thisobj, method, args):
        self.usage = usage
        self.thisobj = thisobj
        self.method = method
        self.args = args

class TupleExtractConstraint:
    def __init__(self, result, thisobj, index):
        self.result = result
        self.thisobj = thisobj
        self.index = index

class TypeConstNode(TypeNode):
    def __init__(self, name):
        super(TypeConstNode, self).__init__()
        self.name = name

    def get_upper_bound(self):
        return (self,)

    def make_node(self, graph):
        graph.node(self.name, self.get_label(), fillcolor="turquoise", style="filled")

OptTypes = dict()

class TypeTupleNode(TypeNode):
    def __init__(self, params):
        super(TypeTupleNode, self).__init__()
        self.params = params
        self.name = "{%s}" % str.join(";", map(str, params))

    def get_upper_bound(self):
        return (self,)

    def get_label(self):
        return "{%s}" % str.join(";", map(lambda type : type.get_repr().get_label(), self.params))

    def make_node(self, graph):
        graph.node(self.name, self.get_label(), fillcolor="darkolivegreen1", style="filled")

class TypeUnionNode(TypeNode):
    def __init__(self, params):
        super(TypeUnionNode, self).__init__()
        self.params = params
        self.name = "(%s)" % str.join("|", map(str, params))

    def get_upper_bound(self):
        return (self,)

    def get_label(self):
        return "(%s)" % str.join("|", map(lambda type : type.get_repr().get_label(), self.params))

    def make_node(self, graph):
        graph.node(self.name, self.get_label(), fillcolor="gold1", style="filled")


class TypeOptNode(TypeNode):
    def __init__(self, internal_type):
        super(TypeOptNode, self).__init__()
        self.internal_type = internal_type
        self.name = internal_type.name + "?"

    def get_upper_bound(self):
        return (self,)

    def get_label(self):
        return "%s?" % self.internal_type.get_repr().get_label()

    def update_upper_bound(self, subtyping):
        progress = False
        for edge in self.inedges:
            new_upper_bound = edge.derivedType.get_upper_bound()
            if new_upper_bound:
                upper_bound_filtered = []
                for ub in new_upper_bound:
                    ub = ub.get_repr()
                    if isinstance(ub, TypeOptNode):
                        upper_bound_filtered.append(ub.internal_type.get_repr())
                    else:
                        upper_bound_filtered.append(ub)
                    progress = progress or self.internal_type.do_update_upper_bound(subtyping, upper_bound_filtered)
        return progress

    def make_node(self, graph):
        graph.node(self.name, self.name, fillcolor="limegreen", style="filled")


def OptType(internal_type):
    if internal_type not in OptTypes:
        OptTypes[internal_type] = TypeOptNode(internal_type)
    return OptTypes[internal_type]


class TypeVarNode(TypeNode):
    def __init__(self, name = None):
        super(TypeVarNode, self).__init__()
        self.name = name or next(unique_var)
        self.parent = self
        self.rank = 0
        self.upper_bound = None

    def get_upper_bound(self):
        if self.get_repr() == self:
            return self.upper_bound
        return self.get_repr().get_upper_bound()

    def get_repr(self):
        if self.parent != self:
            self.parent = self.parent.get_repr()
        return self.parent

    def get_label(self):
        repr = self.get_repr()
        node_label = ""

        node_label = node_label + self.name

        if repr != self:
            node_label = node_label + "({0})".format(repr.get_label())

        if self.upper_bound:
            node_label = node_label + "<={0}".format(map(TypeNode.get_repr, self.upper_bound))
        return node_label

    def make_node(self, graph):
        graph.node(self.name, self.get_label(), fillcolor="pink", style="filled")

    def update_upper_bound(self, subtyping):
        progress = False
        for edge in self.inedges:
            progress = progress or self.do_update_upper_bound(subtyping, edge.derivedType.get_upper_bound())
        return progress

    def do_update_upper_bound(self, subtyping, new_upper_bound):
        upper_bound = self.upper_bound
        if new_upper_bound != None:
            upper_bound = subtyping.merge_upper_bounds(upper_bound, new_upper_bound) if upper_bound != None else new_upper_bound
        if upper_bound:
            upper_bound = tuple(upper_bound)
        if upper_bound != self.upper_bound:
            self.upper_bound = upper_bound
            print "Upper bound for {0} updated to {1}".format(self.get_label(), map(lambda type : type.get_repr().get_label(), upper_bound) if upper_bound != None else None)
            return True
        return False

class TypeSubtypingEdge(object):
    def __init__(self, baseType, derivedType):
        self.baseType = baseType
        self.derivedType = derivedType
        self.satisfied = None

    def make_edge(self, graph):
        if not self.satisfied:
            graph.edge(self.derivedType.name, self.baseType.name, color="red")
        else:
            graph.edge(self.derivedType.name, self.baseType.name, self.satisfied, fontsize="7")

    def try_satisfy(self, subtyping):
        self.satisfied = subtyping.get_coercion(self.baseType, self.derivedType)

    def satisfy(self, coerce_operator):
        self.satisfied = coerce_operator

def collect(types, num):
    global tc
    ret = []
    for type,index in types.iteritems():
        if index == num:
            ret.append(tc.get_constant(type))
    return ret

class SubtypingRules:
    def __init__(self):
        pass

    def get_coercion(self, base, derived):
        base = base.get_repr()
        derived = derived.get_repr()
        if self.is_types_equal(base, derived):
            return "id"
        if isinstance(derived, TypeConstNode) and derived.name == "undef":
            return "from-undef"
        if isinstance(derived, TypeConstNode) and isinstance(base, TypeConstNode):
            if derived.name == "int" and base.name == "double":
                return "int-to-double"
            if derived.name == "float" and base.name == "double":
                return "float-to-double"
            if derived.name == "numeric" and base.name == "int":
                return "numeric-to-int"
            if derived.name == "numeric" and base.name == "float":
                return "numeric-to-float"
            if derived.name == "numeric" and base.name == "double":
                return "numeric-to-double"
        if isinstance(derived, TypeClass) and isinstance(base, TypeClass):
            if base in derived.all_bases:
                return "to-base-class"
        if isinstance(derived, TypeOptNode) and isinstance(base, TypeOptNode):
            internal_coercion = self.get_coercion(base.internal_type, derived.internal_type)
            if internal_coercion == "id":
                return "id"
            return "on-opt-"+internal_coercion if internal_coercion else None
        if isinstance(base, TypeOptNode):
            internal_coercion = self.get_coercion(base.internal_type, derived)
            return internal_coercion + '-and-wrap' if internal_coercion else None
        if isinstance(base, TypeUnionNode):
            candidates = []
            idvariants = []
            for index, variant in enumerate(base.params):
                coercion = self.get_coercion(variant, derived)
                if coercion:
                    candidates.append((index, coercion))
                if coercion == "id":
                    idvariants.append((index, coercion))
            if len(idvariants) == 1:
                return idvariants[0][1] + '-and-pack-{0}'.format(idvariants[0][0])
            if len(candidates) == 1:
                return candidates[0][1] + '-and-pack-{0}'.format(candidates[0][0])
        return None

    def merge_upper_bounds(self, left, right):
        candidates = []
        for l in left:
            for r in right:
                candidates.append(self.merge_upper_bounds_(l, r))
        return reduce(set.intersection, candidates) if candidates else ()

    def unify(self, left, right):
        left = left.get_repr()
        right = right.get_repr()
        if left == right:
            return
        if isinstance(left, TypeVarNode):
            if isinstance(right, TypeVarNode):
                if left.rank < right.rank:
                    left.parent = right
                elif left.rank > right.rank:
                    right.parent = left
                else:
                    right.parent = left
                    left.rank = left.rank + 1
            else:
                left.parent = right
            return
        if isinstance(right, TypeVarNode):
            right.parent = left
            return
        if (isinstance(left, TypeTupleNode) and isinstance(right,TypeTupleNode)) or \
            isinstance(left, TypeUnionNode) and isinstance(right,TypeUnionNode):
            if len(left.params) == len(right.params):
                for (l,r) in zip(left.params, right.params):
                    self.unify(l, r)
        if isinstance(left, TypeOptNode) and isinstance(right,TypeOptNode):
            self.unify(left.internal_type, right.internal_type)

    def is_types_equal(self, left, right):
        left = left.get_repr()
        right = right.get_repr()
        if left == right:
            return True

        if (isinstance(left, TypeTupleNode) and isinstance(right, TypeTupleNode)) or \
            (isinstance(left, TypeUnionNode) and isinstance(right, TypeUnionNode)):

            if len(left.params) == len(righ.params):
                for (l,r) in zip(left.params, right.params):
                    if not self.is_types_equal(left, right):
                        return False
                return True
            return False

        if isinstance(left, TypeOptNode) and isinstance(right, TypeOptNode):
            return self.is_types_equal(left.internal_type, right.internal_type)
        return False

    def merge_upper_bounds_(self, left, right):
        left = left.get_repr()
        right = right.get_repr()
        if left == right:
            return (left,)
        if isinstance(left, TypeConstNode) and left.name == "undef":
            return (left,)
        if isinstance(right, TypeConstNode) and right.name == "undef":
            return (right,)
        if isinstance(left, TypeConstNode) and isinstance(right, TypeConstNode):
            numeric_types = {"numeric":1, "int":2,"float":2,"double":3}
            if left.name in numeric_types and right.name in numeric_types:
                if numeric_types[left.name] < numeric_types[right.name]:
                    return (right,)
                elif numeric_types[left.name] > numeric_types[right.name]:
                    return (left,)
                else:
                    return collect(numeric_types, max(numeric_types[left.name], numeric_types[right.name])+1)
        if isinstance(left, TypeClass) and isinstance(right, TypeClass):
            if left in right.all_bases:
                return (right,)
            if right in left.all_bases:
                return (left,)
            common_bases = left.all_bases & right.all_bases
            return common_bases
        if isinstance(left, TypeTupleNode) and isinstance(right, TypeTupleNode):
            if len(left.params) == len(righ.params):
                for (l,r) in zip(left.params, right.params):
                    if not self.is_types_equal(left, right):
                        return ()
                return (left,)
            return ()
        if isinstance(left, TypeUnionNode) and isinstance(right, TypeUnionNode):
            if len(left.params) == len(righ.params):
                for (l,r) in zip(left.params, right.params):
                    if not self.is_types_equal(left, right):
                        return ()
                return (left,)
            return ()
        if isinstance(left, TypeOptNode) and isinstance(right, TypeOptNode):
            types = self.merge_upper_bounds_(left.internal_type, right.internal_type)
            return map(OptType, types)
        if isinstance(left, TypeOptNode):
            types = self.merge_upper_bounds_(left.internal_type, right)
            return map(OptType, types)
        if isinstance(right, TypeOptNode):
            types = self.merge_upper_bounds_(left, right.internal_type)
            return map(OptType, types)
        return ()

class TypeContext:
    def __init__(self):
        self.nodes = set()
        self.constants = dict()
        self.edges = dict()
        self.calls = []
        self.extracts = []

    def get_constant(self, name):
        if name not in self.constants:
            node = TypeConstNode(name)
            self.constants[name] = node
            self.add_node(node)
        return self.constants[name]

    def add_node(self, node):
        self.nodes.add(node)

    def add_nodes(self, nodes):
        self.nodes.update(set(nodes))

    def add_method_constraint(self, usage, thisobj, method, args):
        self.calls.append(MethodCallConstraint(usage, thisobj, method, args))

    def add_tuple_extract_constraint(self, result, thisobj, index):
        self.extracts.append(TupleExtractConstraint(result, thisobj, index))

    def add_edge(self, base, derived):
        if base not in self.nodes:
            self.add_node(base)
        if derived not in self.nodes:
            self.add_node(derived)
        if (base, derived) not in self.edges:
            edge = TypeSubtypingEdge(base, derived)
            self.edges[(base, derived)] = edge
            base.add_inedge(edge)
            derived.add_outedge(edge)
            return True
        return False

    def unify_edges(self, subtyping):
        for (base,derived), edge in self.edges.iteritems():
            if isinstance(base, TypeTupleNode) or isinstance(derived, TypeTupleNode):
                subtyping.unify(base, derived)

    def satisfy_edges(self, subtyping):
        for edge in self.edges.itervalues():
            edge.try_satisfy(subtyping)

    def update_bounds(self, subtyping):
        while any(map(lambda node:node.update_upper_bound(subtyping), self.nodes.copy())):
            pass

    def solve_constraints(self, subtyping):
        progress = False
        for call in self.calls:
            thisobj = call.thisobj.get_repr()
            if isinstance(thisobj, TypeVarNode):
                if thisobj.get_upper_bound():
                    thisobj = thisobj.get_upper_bound()
            if isinstance(thisobj, TypeClass) and call.method in thisobj.methods and bound:
                method = thisobj.methods[call.method]
                if len(method.params) == len(call.args):
                    for (param, arg) in zip(method.params, call.args):
                        progress = progress or self.add_edge(arg, param)
                progress = progress or self.add_edge(call.usage, method.ret)
        for extract in self.extracts:
            thisobj = extract.thisobj.get_repr()
            if isinstance(thisobj, TypeTupleNode):
                if len(thisobj.params) >= extract.index:
                    progress = progress or self.add_edge(extract.result, thisobj.params[extract.index].get_repr())
        return progress

    def show(self):
        graph = graphviz.Digraph()
        for node in self.nodes:
            node.make_node(graph)
        for edge in self.edges.itervalues():
            edge.make_edge(graph)
        graph.view()

    def resolve_type_vars(self):
        progress = False
        for node in self.nodes:
            node = node.get_repr()
            if isinstance(node, TypeVarNode):
                if node.upper_bound and len(node.upper_bound) == 1:
                    node.parent = node.upper_bound[0]
                    progress = True
        return progress

tc = TypeContext()

"""
    b = int
    c = float

    (int|double)b
    (int|double)c
"""

a = TypeVarNode("a")
b = TypeVarNode("b")
c = TypeVarNode("c")
tc.add_nodes((a,b,c))

tc.add_edge(b, tc.get_constant("int"))
tc.add_edge(c, tc.get_constant("numeric"))

union = TypeUnionNode([tc.get_constant("int"), tc.get_constant("double")])

tc.add_edge(union, b)
tc.add_edge(union, c)

"""
tc.add_edge(b, tc.get_constant("int"))
tc.add_edge(c, tc.get_constant("int"))

tc.add_edge(d, a)
tc.add_edge(d, c)
tc.add_edge(e, d)
tc.add_edge(e, b)
"""

subtyping = SubtypingRules()

tc.unify_edges(subtyping)

progress = True
while progress:
    tc.update_bounds(subtyping)

    while tc.solve_constraints(subtyping):
        tc.update_bounds(subtyping)

    progress = tc.resolve_type_vars()

tc.satisfy_edges(subtyping)

tc.show()