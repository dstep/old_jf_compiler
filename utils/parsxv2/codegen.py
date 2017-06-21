import itertools
import grammar
import typesystem
import re

def isplit(iterable,spliters):
    return [list(g) for k,g in itertools.groupby(iterable,lambda x:x in spliters) if not k]

class Indentation:
    def __init__(self, stream):
        self.stream = stream
    def __enter__(self):
        self.stream.indent_level = self.stream.indent_level + "\t"
    def __exit__(self, type, value, traceback):
        self.stream.indent_level = self.stream.indent_level[:-1]

class Stream:
    def __init__(self, file):
        self.file = file
        self.indent_level = ""
        self.current_line = ""

    def write(self, ln):
        parts = str.split(ln, "\n")
        for part in parts[:-1]:
            self._add_to_current_line(part)
            self._flush_line()
        self._add_to_current_line(parts[-1])

    def writeln(self, ln):
        self.write(ln)
        self._flush_line()

    def _add_to_current_line(self, ln):
        if len(ln) == 0:
            return
        if len(self.current_line) == 0:
            self.current_line = self.indent_level
        self.current_line = self.current_line + ln

    def _flush_line(self):
        self.file.write(self.current_line + "\n")
        self.current_line = ""

    def flush(self):
        self._flush_line()

class ConstantArray:
    def __init__(self, type, name):
        self.type = type
        self.name = name
        self.values = []
    def add_value(self, value):
        self.values.append(value)
    def finish_group(self):
        self.values.append(None)
    def output(self, stream):
        groups = isplit(self.values, (None,))
        stream.writeln("%s %s[] = {" % (self.type, self.name))
        with Indentation(stream):
            for group in groups:
                line = ""
                for value in group:
                    line += str(value) + ", "
                stream.writeln(line)
        stream.writeln("};")

class PlainCode:
    def __init__(self, code):
        self.code = code
    def output(self, stream):
        stream.writeln(self.code)

class Block:
    def __init__(self, indent = False, stmts = []):
        self.stmts = stmts[:]
        self.indent = indent
    def add(self, stmt):
        self.stmts.append(stmt)
        return stmt
    def output(self, stream):
        if self.indent:
            with Indentation(stream):
                for stmt in self.stmts:
                    stmt.output(stream)
        else:
            for stmt in self.stmts:
                    stmt.output(stream)

class NamedBlock(Block):
    def __init__(self, pre, post):
        Block.__init__(self, True)
        self.pre = pre
        self.post = post

    def output(self, stream):
        stream.writeln(self.pre)
        Block.output(self, stream)
        stream.writeln(self.post)

class SwitchStmt:
    def __init__(self, expr):
        self.expr = expr
        self.branches = []
        self.default = None
    def add_case(self, tag):
        block = NamedBlock("case %s:{" % tag, "}break;")
        self.branches.append(block)
        return block
    def add_default(self):
        block = NamedBlock("default:{", "}break;")
        self.default = block
        return block
    def output(self, stream):
        stream.writeln("switch ( %s ){" % self.expr)
        with Indentation(stream):
            for branch in self.branches:
                branch.output(stream)
            if self.default != None:
                self.default.output(stream)
        stream.writeln("}")

class IfStmt:
    def __init__(self):
        self.branches = []
        self.def_branch = None
    def add_branch(self, cond, stmt):
        self.branches.append((cond, stmt))
        return self
    def add_def_branch(self, stmt):
        if self.def_branch == None:
            raise RuntimeError("two default branches")
        self.def_branch = stmt
        return self
    def output(self, stream):
        if len(self.branches) > 0:
            stream.writeln("if ( %s ){" % self.branches[0][0])
            with Indentation(stream):
                self.branches[0][1].output(stream)
            stream.write("}")
            for (cond,stmt) in self.branches[1:]:
                stream.writeln(" else if ( %s ){" % cond)
                with Indentation(stream):
                    stmt.output(stream)
                stream.write("}")
            if self.def_branch != None:
                stream.writeln(" else {")
                with Indentation(stream):
                    self.def_branch.output(stream)
                stream.writeln("}")
            else:
                stream.writeln("")
        else:
            if self.def_branch != None:
                self.def_branch.output(stream)

Consume = object()
class Run:
    def __init__(self, action):
        self.action = action

class State:
    def __init__(self, atom):
        self.atom = atom
        self.transitions = dict()
        self.used = False
        self.sync = dict()
        self.skip_sync = None
        self.expects = set()

    def add_transition(self, term, action, push):
        self.transitions[term] = (action, push)

    def __repr__(self):
        return str(self.atom)

class TakenRule:
    def __init__(self, state, term, actions, states):
        self.actions = actions
        self.state = state
        self.states = states
        self.term = term
        self.consumed = Consume in actions

class SyncRule:
    def __init__(self, state, term, cost, actions, states):
        self.term = term
        self.state = state
        self.cost = cost
        self.actions = actions
        self.states = states

class Codegen:
    def __init__(self, grammar):
        self.grammar = grammar
        self.states = dict()
        self.merge = []
        self.export = []
        self.atoms = []
        self.merge_solutions = dict()

    def assign_states(self):
        for nt in self.grammar.non_terminals:
            type = nt.type.get_as_single_constant()
            if type != None and hasattr(nt, "export"):
                state = self.export_state(nt)
                self.export.append((state, nt.export, type))

        merge_index = 0
        while merge_index < len(self.merge):
            state = self.merge[merge_index]
            merge_states = len(self.merge)
            merge_index = merge_index + 1
            state.transitions = dict()
            state.expects = set()
            actions = []
            for index, atom in enumerate(state.atom):
                state.expects.update(atom.expects)
                for (k,v) in atom.transitions.iteritems():
                    if k not in state.transitions or k == None:
                        state.transitions[k] = (actions + v[0], self.compress_sequence(v[1] + list(state.atom[index + 1:]), True))
                    if k == None:
                        actions.extend(v[0])

        self.collect_dead_states(True)

        progress = True
        while progress:
            progress = False
            for state in self.atoms[:]:
                if state.skip_sync == None:
                    progress = True
                    atom = state.atom
                    for (term,(cost, rule)) in atom.sync.iteritems():
                        if cost > 0 and term != None:
                            continue
                        sequence = []
                        for a in rule:
                            if isinstance(a, grammar.RuleIdentity):
                                continue
                            sequence.append(a)
                        (lhs, rhs) = self.split_sync_sequence(sequence, term)
                        if term == None:
                            if len(rhs) > 0:
                                raise RuntimeError("Skip for atom %s contains non-skip sequence" % atom)
                            state.skip_sync = (cost, lhs)
                        else:
                            state.sync[term] = (cost, lhs, rhs)
                    if state.skip_sync == None:
                        raise RuntimeError("No skip sequence is generated for atom %s" % atom)
            self.collect_dead_states(False)

        self.collect_dead_states(False)

        for state in self.merge:
            state.sync = dict()
            (skip_cost, skip_action) = (0, [])
            for index, atom in enumerate(state.atom):
                for (k,(cost, actions, pushes)) in atom.sync.iteritems():
                    if k not in state.sync or cost + skip_cost < state.sync[k][0]:
                        state.sync[k] = (cost + skip_cost, skip_action + actions, self.compress_sequence(pushes + list(state.atom[index+1:]), False))
                (cost, rule) = atom.skip_sync
                skip_cost = skip_cost + cost
                skip_action = skip_action + rule
            state.skip_sync = (skip_cost, skip_action)

        self.collect_dead_states(False, False)

        self.ordered_states = []
        self.rules = []
        self.sync_rules = []
        index = 1

        for k,v in self.states.iteritems():
            v.index = index
            self.ordered_states.append(v)
            for (t,(act,st)) in v.transitions.iteritems():
                self.rules.append(TakenRule(v, t, act, st))
            for (t, (cost, act, st)) in v.sync.iteritems():
                if t not in v.transitions:
                    self.sync_rules.append(SyncRule(v, t, cost, act, st))
            (cost, act) = v.skip_sync
            self.sync_rules.append(SyncRule(v, None, cost, act, []))
            index = index + 1

        self.last_nonshifting_rule = 0
        rule_index = 1
        self.rules.sort(key=lambda t:t.consumed)
        for rule in self.rules:
            if not rule.consumed:
                self.last_nonshifting_rule = rule_index
            rule.index = rule_index
            rule_index = rule_index + 1
        sync_rule_index = 1
        for rule in self.sync_rules:
            rule.index = sync_rule_index
            sync_rule_index = sync_rule_index + 1

        print "Active states: %s" % (index - 1)
        print "Active rules: %s" % (rule_index - 1)

    def split_sync_sequence(self, seq, term):
        lhs = []
        def make_states(seq):
            return self.compress_sequence(map(lambda x : self.export_state(x), seq), False)
        for (index, atom) in enumerate(seq):
            if atom == term:
                return (lhs, make_states(seq[index+1:]))
            elif isinstance(atom, grammar.Action) or isinstance(atom, grammar.Terminal):
                lhs.append(atom)
            else:
                raise RuntimeError("Invalid sync sequence generated (bad atom before token occurence): %s for %s" % (seq, term))
        if term != None:
            raise RuntimeError("Invalid sync sequence generated (no token occurence): %s for %s" % (seq, term))
        return (lhs, [])

    def collect_dead_states(self, mark_atoms = True, mark_partials = True):
        marked = set()
        def mark_state(marked, state):
            if state.used:
                return
            marked.add(state)
            state.used = True
            if mark_partials:
                if isinstance(state.atom, tuple):
                    for atom in state.atom:
                        mark_state(marked, atom)
            for v in state.transitions.itervalues():
                for st in v[1]:
                    mark_state(marked, st)
            for (term, (cost, atoms, rule)) in state.sync.iteritems():
                if term not in state.transitions:
                    for st in rule:
                        mark_state(marked, st)

        for state in self.export:
            mark_state(marked, state[0])

        if mark_atoms:
            for state in self.atoms:
                mark_state(marked, state)

        self.states = {k:v for (k,v) in self.states.iteritems() if v.used}
        for state in marked:
            state.used = False

    def merge_state(self, states):
        if states not in self.states:
            state = State(states)
            self.merge.append(state)
            self.states[states] = state
        return self.states[states]

    def solve_merge(self, states):
        mem = self.merge_solutions
        if states in mem:
            return mem[states]
        def solve(states):
            if len(states) == 1:
                return [states[0]]
            elif states in self.states:
                return [self.states[states]]
            else:
                best = None
                for i in xrange(1,len(states)):
                    left = self.solve_merge(states[:i])
                    right = self.solve_merge(states[i:])
                    if best == None or len(best) > len(left) + len(right):
                        best = left + right
                return best
        solution = solve(states)
        mem[states] = solution
        return solution


    def merge_states(self, states, allow_new):
        if allow_new:
            return [self.merge_state(states)]
        else:
            return self.solve_merge(states)

    def compressible(self, state):
        if None not in state.transitions:
            return False
        if len(state.transitions[None][1]) > 0:
            return False
        if len(state.transitions) == 1:
            return False
        if len(state.transitions[None][0]) == 0 and len(state.transitions[None][1]) == 0:
            return True
        return False

    def compress_sequence(self, sequence, allow_new):
        folded_productions = []
        seq = []
        for prodstate in sequence:
            if not self.compressible(prodstate) or prodstate in seq:
                if len(seq) == 1:
                    folded_productions.append(seq[0])
                elif len(seq) > 1:
                    folded_productions.extend(self.merge_states(tuple(seq), allow_new))
                seq = []
                folded_productions.append(prodstate)
            else:
                seq.append(prodstate)
        if len(seq) == 1:
            folded_productions.append(seq[0])
        elif len(seq) > 1:
            folded_productions.extend(self.merge_states(tuple(seq), allow_new))
        return folded_productions

    def export_state(self, atom):
        if atom not in self.states:
            state = State(atom)
            self.states[atom] = state
            self.atoms.append(state)
            state.expects = atom.expects
            state.ready = False

            if hasattr(atom, "transitions"):
                for (term, production) in atom.transitions.iteritems():
                    actions = []
                    state_production = []
                    consumed = False

                    for a in production:
                        if isinstance(a, grammar.RuleIdentity):
                            continue
                        a_state = self.export_state(a)
                        if consumed:
                            #if a_state.ready and len(state_production) == 0 and len(a_state.transitions) == 1 and None in a_state.transitions:
                            #    transition = next(a_state.transitions.itervalues())
                            #    actions.extend(transition[0])
                            #    state_production.extend(transition[1])
                            #else:
                                state_production.append(a_state)
                        else:
                            if term in a_state.transitions:
                                actions.extend(a_state.transitions[term][0])
                                state_production.extend(a_state.transitions[term][1])
                                if Consume in actions or len(state_production) > 0:
                                    consumed = True
                            elif None in a_state.transitions:
                                actions.extend(a_state.transitions[None][0])
                                state_production.extend(a_state.transitions[None][1])
                                if Consume in actions or len(state_production) > 0:
                                    consumed = True
                            else:
                                state_production.append(a_state)
                                consumed = True

                    state.add_transition(term, actions, self.compress_sequence(state_production, True))
            if isinstance(atom, grammar.Terminal):
                state.add_transition(atom, [Consume], [])
            if isinstance(atom, grammar.Action):
                state.add_transition(None, [Run(atom)], [])

            state.ready = True
        return self.states[atom]

    def codegen(self, stream):
        self.assign_states()
        glob = Block()
        decl = Block()
        for (state, name, type) in self.export:
            decl.add(PlainCode("parsx_symbol_state(%s,%s,%s);" % (state.index, name, type)))

        glob.add(decl)
        impl = NamedBlock("#if defined(parsx_impl)", "#endif")


        parse_table = impl.add(PlainCode("short parsx_table[parsx_max_token_id + 3][%s] = {0};" % len(self.ordered_states)))
        sync_cost_table = impl.add(ConstantArray("const unsigned char", "parsx_sync_cost_table"))
        sync_cost_table.add_value(0)
        for rule in self.sync_rules:
            sync_cost_table.add_value(rule.cost)

        parse_table_gen = impl.add(NamedBlock("struct parsx_parse_table_gen{parsx_parse_table_gen(){", "}};"))
        for rule in self.rules:
            if rule.term != None:
                parse_table_gen.add(PlainCode("parsx_table[parsx_token(%s)][%s] = %s;" % (rule.term.get_id(), rule.state.index, rule.index)))
            else:
                parse_table_gen.add(PlainCode("parsx_table[parsx_max_token_id + 1][%s] = %s;" % (rule.state.index, rule.index)))
        for rule in self.sync_rules:
            if rule.term != None:
                parse_table_gen.add(PlainCode("parsx_table[parsx_token(%s)][%s] = %s;" % (rule.term.get_id(), rule.state.index, -rule.index)))
            else:
                parse_table_gen.add(PlainCode("parsx_table[parsx_max_token_id + 2][%s] = %s;" % (rule.state.index, -rule.index)))
        impl.add(PlainCode("const parsx_parse_table_gen parsx_init_table;"))

        rule_states_table = impl.add(ConstantArray("const short", "parsx_rule_state_table"))
        table_index = 0
        for rule in self.rules:
            #print "Rule from %s, (%s) -> %s => [%s,%s]" % (rule.state, rule.term, rule.index, rule.actions, rule.states)
            rule.table_index = table_index
            rule_states_table.add_value(rule.state.index)
            table_index = table_index + 1
            for state in reversed(rule.states):
                rule_states_table.add_value(state.index)
                table_index = table_index + 1
            rule_states_table.add_value(0)
            rule_states_table.finish_group()
            table_index = table_index + 1

        rule_states_table_index = impl.add(ConstantArray("const short", "parsx_rule_state_table_index"))
        rule_states_table_index.add_value(0)
        for rule in self.rules:
            rule_states_table_index.add_value(rule.table_index)

        parse_step = impl.add(NamedBlock("parsx_step_func_begin()", "parsx_step_func_end()"))
        commit_step = impl.add(NamedBlock("parsx_commit_func_begin()", "parsx_commit_func_end()"))
        undo_step = impl.add(NamedBlock("parsx_undo_func_begin()", "parsx_undo_func_end()"))
        sync_cost = impl.add(NamedBlock("parsx_sync_cost_func_begin()", "parsx_sync_cost_func_end()"))
        sync_func = impl.add(NamedBlock("parsx_sync_func_begin()", "parsx_sync_func_end()"))

        sync_if = sync_cost.add(IfStmt())
        sync_block = Block()
        sync_if.add_branch("parsx_sync_token <= parsx_max_token_id", sync_block)
        sync_block.add(PlainCode("short parsx_taken_action = parsx_table[parsx_sync_token][parsx_sync_state];"))
        sync_block.add(PlainCode("if ( parsx_taken_action > 0 ) return 0;"))
        sync_block.add(PlainCode("if ( parsx_taken_action < 0 ) return parsx_sync_cost_table[-parsx_taken_action];"))
        sync_cost.add(PlainCode("return parsx_sync_cost_table[-parsx_table[parsx_max_token_id + 2][parsx_sync_state]];"))

        sync_func.add(PlainCode("short parsx_taken_action = 0;"))
        sync_block = Block()
        sync_func.add(IfStmt()).add_branch("parsx_lookahead_token <= parsx_max_token_id", sync_block)
        sync_block.add(PlainCode("parsx_taken_action = parsx_table[parsx_lookahead_token][parsx_current_state];"))
        sync_func.add(PlainCode("if ( parsx_taken_action == 0 ) parsx_taken_action = parsx_table[parsx_max_token_id + 2][parsx_current_state];"))

        def generate_action_code(block, action):
            type = action.type
            (params, result) = typesystem.split_arrow(type)
            for (index, param) in reversed(list(enumerate(reversed(params)))):
                if not typesystem.is_type_empty(param):
                    action_block.add(PlainCode("%s %s = parsx_pop_value(%s);" % (param, "_parsx_%s" % (index + 1), param)))
            if typesystem.is_type_empty(result):
                action_block.add(PlainCode(action.code))
            else:
                code = re.sub("\$([0-9]+)", "_parsx_\g<1>", action.code)
                action_block.add(PlainCode("parsx_push_value(%s, %s);" % (result, code)))

        sync_func.add(PlainCode("if ( parsx_taken_action > 0 ) return;"))
        sync_func.add(PlainCode("parsx_pop_state();"))
        sync_switch = sync_func.add(SwitchStmt("-parsx_taken_action"))
        sync_switch.add_case(0)
        for rule in self.sync_rules:
            sync_case = sync_switch.add_case(rule.index)
            for action in rule.actions:
                if isinstance(action, grammar.Terminal):
                    sync_case.add(PlainCode("parsx_insert_token(%s);" % action.get_id()))
                elif isinstance(action, grammar.Action):
                    action_block = sync_case.add(NamedBlock("{", "}"))
                    generate_action_code(action_block, action)

            if rule.term != None:
                sync_case.add(PlainCode("parsx_shift_token();"))
                sync_case.add(PlainCode("parsx_commit_token();"))

            for state in reversed(rule.states):
                sync_case.add(PlainCode("parsx_push_state(%s);" % state.index))

        commit_loop = commit_step.add(NamedBlock("while ( parsx_has_queued_action ){\n\tAction parsx_action = parsx_pop_queued_action;", "}"))
        commit_switch = commit_loop.add(SwitchStmt("parsx_action"))
        commit_switch.add_case("0")
        for rule in self.rules:
            br = commit_switch.add_case(rule.index)
            for action in rule.actions:
                if action == Consume:
                    br.add(PlainCode("parsx_commit_token();"))
                else:
                    action_block = br.add(NamedBlock("{", "}"))
                    action = action.action
                    generate_action_code(action_block, action)

        commit_loop.add(IfStmt().add_branch("parsx_action > %s" % self.last_nonshifting_rule, PlainCode("return true;")))

        undo_loop = undo_step.add(NamedBlock("while ( parsx_has_queued_action ){", "}"))
        undo_loop.add(PlainCode("Action parsx_action = parsx_pop_last_queued_action;"))
        undo_loop.add(PlainCode("const short* parsx_pushed_states = parsx_rule_state_table + parsx_rule_state_table_index[parsx_action];"))
        undo_loop.add(PlainCode("const short parsx_pushed_state = *parsx_pushed_states;"))
        undo_loop.add(PlainCode("while ( *(++parsx_pushed_states) ) parsx_pop_state();"))
        undo_loop.add(PlainCode("parsx_push_state(parsx_pushed_state);"))
        undo_loop.add(IfStmt().add_branch("parsx_action > %s" % self.last_nonshifting_rule, PlainCode("parsx_unshift_token();")))

        parse_step_loop = parse_step.add(NamedBlock("while( parsx_has_state ){\n\tState parsx_current_state_ = parsx_current_state;", "}"))
        parse_step_loop.add(PlainCode("Action parsx_taken_action = parsx_table[parsx_lookahead_token][parsx_current_state_];"))
        parse_step_loop.add(PlainCode("if ( parsx_taken_action <= 0 ) { parsx_taken_action = parsx_table[parsx_max_token_id + 1][parsx_current_state_];"))
        parse_step_loop.add(PlainCode("if ( parsx_taken_action <= 0 ) return false; }"))
        parse_step_loop.add(PlainCode("parsx_queue_action(parsx_taken_action);"))
        parse_step_loop.add(PlainCode("parsx_pop_state();"))
        parse_step_loop.add(PlainCode("const short* parsx_pushed_states = parsx_rule_state_table + parsx_rule_state_table_index[parsx_taken_action];"))
        parse_step_loop.add(PlainCode("while ( *(++parsx_pushed_states) ) parsx_push_state(*parsx_pushed_states);"))
        parse_step_loop.add(PlainCode("if ( parsx_taken_action > %s ) { parsx_shift_token(); return true; }" % self.last_nonshifting_rule))

        expects_list = impl.add(ConstantArray("const parsx_expect_type", "parsx_expect_table"))
        expects_list_index = impl.add(ConstantArray("const unsigned int", "parsx_expect_table_index"))
        expects_list_index.add_value(0)
        expects_list_index.add_value(0)
        expect_index = 0
        for state in self.ordered_states:
            if len(state.expects) > 0:
                expects_list_index.add_value(expect_index)
                start_index = expect_index
                for expect in state.expects:
                    if isinstance(expect, grammar.Terminal):
                        expects_list.add_value("parsx_expect_token(%s)" % expect.get_id())
                    else:
                        expects_list.add_value("parsx_expect_name(%s)" % expect)
                    expect_index = expect_index + 1
                expects_list_index.add_value(expect_index - start_index)
                expects_list.finish_group()
            else:
                expects_list_index.add_value(0)
                expects_list_index.add_value(0)

        expect_func = impl.add(NamedBlock("parsx_expected_func_begin()", "parsx_expected_func_end()"))
        expect_func.add(PlainCode("const unsigned int* parsx_expect_index = parsx_expect_table_index + parsx_expect_state * 2;"))
        expect_func.add(PlainCode("const parsx_expect_type *parsx_expects = parsx_expect_table + parsx_expect_index[0];"))
        expect_func.add(PlainCode("unsigned int parsx_expect_count = parsx_expect_index[1];"))
        expect_func.add(PlainCode("while ( parsx_expect_count-- ) parsx_expect(*(parsx_expects++));"))

        sync_mask = impl.add(NamedBlock("parsx_sync_mask_table_begin()", "parsx_sync_mask_table_end()"))
        sync_mask.add(PlainCode("parsx_sync_mask(0)"))
        for state in self.ordered_states:
            syncs = []
            for (t, sync) in state.sync.iteritems():
                if t != None:
                    syncs.append(t)
            syncs = [str(len(syncs))] + map(lambda t : "parsx_token(%s)" % t.get_id(), syncs)
            sync_mask.add(PlainCode("parsx_sync_mask(%s)" % str.join(",", syncs)))

        glob.add(impl)
        glob.output(stream)
        stream.flush()
