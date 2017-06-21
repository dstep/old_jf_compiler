from collections import defaultdict

class NFA2DFASet:
    def __init__(self):
        self.nfas = set()
        self.next_nfa_index = 0
        self.dfas = dict()

    def convert_nfa(self, nfa):
        return self.get_dfa(nfa.get_closure())

    def get_dfa(self, nfas):
        index = 0
        for nfa in nfas:
            self.add(nfa)
            index = index + 2 ** nfa.index
        if index in self.dfas:
            return self.dfas[index]
        dfa = DFAState(nfas)
        self.dfas[index] = dfa
        trans = defaultdict(lambda: set())
        
        for nfa in nfas:
            for k, v in nfa.transitions.iteritems():
                map(lambda r:trans[k].update(r.get_closure()), v)
        
        for k,v in trans.iteritems():
            dfa.transitions[k] = self.get_dfa(v)
        return dfa
        
    def add(self, nfa):
        if nfa not in self.nfas:
            self.nfas.add(nfa)
            nfa.index = self.next_nfa_index
            self.next_nfa_index = self.next_nfa_index + 1    

class DFAState:
    def __init__(self, nfas):
        self.nfas = nfas
        self.transitions = dict()
        self.finals = set()
        for nfa in nfas:
            if nfa.final:
                self.finals.add(nfa.final)

    def show(self):
        showed = [self]
        i = 0
        while i < len(showed):
            showed[i]._show(i, showed)
            i = i + 1

    def _show(self, i, showed):
        print("State {}: {}".format(i, self.finals))
        for k,v in self.transitions.iteritems():
            if v in showed:
                j = showed.index(v)
            else:
                j = len(showed)
                showed.append(v)                
            print("{} -> State {}".format(k, j))

def find_dfas(dfa, dfas):
    if dfa in dfas:
        return
    dfas.add(dfa)
    for v in dfa.transitions.itervalues():
        find_dfas(v, dfas)

def update_dfa(dfa, represent, updated):
    udfa = represent[dfa]
    if udfa in updated:
        return udfa
    updated.add(udfa)
    for k,v in udfa.transitions.iteritems():
        udfa.transitions[k] = update_dfa(v, represent, updated)
    return udfa

def minimize_dfa(dfa):
    dfas = set()
    find_dfas(dfa, dfas)
    dfalist = list(dfas)

    disjoint = set()
    for dfa1 in dfalist:
        for dfa2 in dfalist:
            if dfa1 <> dfa2 and (dfa1.finals <> dfa2.finals or dfa1.transitions.keys() <> dfa2.transitions.keys()):
                disjoint.add((dfa1, dfa2))

    progress = True
    while progress:
        progress = False
        for dfa1 in dfalist:
            for dfa2 in dfalist:
                if dfa1 <> dfa2 and ((dfa1, dfa2) not in disjoint):
                    for k in dfa1.transitions:
                        if (dfa1.transitions[k], dfa2.transitions[k]) in disjoint:
                            disjoint.add((dfa1, dfa2))
                            progress = True

    represent = dict()
    updated = set()
    for dfa1 in dfalist:
        for dfa2 in dfalist:
            if (dfa1, dfa2) not in disjoint:
                represent[dfa1] = dfa2
                break

    return update_dfa(dfa, represent, updated)
