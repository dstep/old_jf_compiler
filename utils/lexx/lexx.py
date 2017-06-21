from regex import *
from nfa import *
from dfa import *
from codegenc import *

import re

import sys

codegen = CodegenC()
prologue = ""

if len(sys.argv) == 3:
    input = sys.argv[1]
    output = sys.argv[2]
else:
    input = "input.lexx"
    output = "lexx.c"

file = open(input)
lines = file.readlines()
line = 0
allstates = ["INITIAL"]

try:
    while True:
        if re.match('=+', lines[line]):
            break
        prologue = prologue + lines[line]
        line = line + 1
    line = line + 1
    while True:
        if re.match('=+', lines[line]):
            break
        ln = lines[line].translate(None, "\n\r\t ")
        codegen.add_state(ln)
        allstates.append(ln)
        line = line + 1
    line = line + 1

    res = []
    act = ""

    state = 0

    while line < len(lines):
        ln = lines[line]
        if len(ln) > 0:
            if ln[0] in "\t ":
                if len(res) == 0:
                    raise Exception("Action without pattern")
                if state == 0:
                    actline = line
                act = act + ln
                state = 1
            else:
                ln = ln.translate(None, "\n\r\t")
                if len(ln) > 0:
                    if state == 1:
                        act = Action(act, "at line {0}".format(actline))
                        for r in res:
                            for st in r[0]:
                                if r[1] == None:
                                    codegen.add_state_eof_action(st, act)
                                else:
                                    codegen.add_action(st, r[1], act)
                        act = ""
                        state = 0
                        res = []

                    if ln[0] == '<':
                        match = re.match("<([^>]*)>(.*)", ln)
                        states = match.group(1).translate(None, "\n\r\t ").split(',')
                        if len(states) == 1 and states[0] == "ALL":
                            states = allstates
                        re_text = match.group(2)
                    else:
                        states = ["INITIAL"]
                        re_text = ln
                    if re_text == "<EOF>":
                        res.append((states, None))
                    else:
                        re_obj = ParseRE(re_text.strip()).do()
                        res.append((states, re_obj))

        line = line + 1

    if state == 1:
        act = Action(act, "at line {0}".format(actline))
        for r in res:
            for st in r[0]:
                if r[1] == None:
                    codegen.add_state_eof_action(st, act)
                else:
                    codegen.add_action(st, r[1], act)
    else:
        raise Exception("Pattern without code")

except ParseError as e:
    print "At line {0}: {1}".format(line, e)

codegen.prologue = prologue

codegen.generate()

f = open(output, "w")
codegen.emmit(f)
f.close()
