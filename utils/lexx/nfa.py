from collections import defaultdict

class NFAState:
    def __init__(self, final = None):
        self.transitions = defaultdict(lambda: [])
        self.etrans = []
        self.final = final
        self.closure = None

    def add_etrans(self, nfa):
        self.etrans.append(nfa)

    def add_trans(self, chars, nfa):
        for ch in chars:
            self.transitions[ch].append(nfa)

    def find_closure(self, closure):
        if self in closure:
            return
        if self.closure <> None:
            closure.update(self.closure)
        else:
            closure.add(self)
            for e in self.etrans:
                e.find_closure(closure)

    def get_closure(self):
        if self.closure <> None:
            return self.closure
        closure = set()
        self.find_closure(closure)
        self.closure = closure
        return closure

def make_nfa(re, start, final):
    return re_to_nfa(re, start, NFAState(final))

def re_to_nfa(re, nfaStart, nfaEnd):
    class REToNFA:
        def __init__(self, start, end):
            self.start = start
            self.end = end
        def visitEmpty(self):
            self.start.add_etrans(self.end)
        def visitOneOf(self, chars):
            self.start.add_trans(chars, self.end)
        def visitConcat(self, left, right):
            midstate = NFAState()
            left.visit(REToNFA(self.start, midstate))
            right.visit(REToNFA(midstate, self.end))
        def visitChoice(self, left, right):
            left.visit(REToNFA(self.start, self.end))
            right.visit(REToNFA(self.start, self.end))
        def visitRepeat(self, re):
            lstate = NFAState()
            rstate = NFAState()
            re.visit(REToNFA(lstate, rstate))
            self.start.add_etrans(lstate)
            self.start.add_etrans(self.end)
            rstate.add_etrans(lstate)
            rstate.add_etrans(self.end)        
    re.visit(REToNFA(nfaStart, nfaEnd))
