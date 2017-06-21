import string

mapOrd = lambda x : map(ord, x)

printable_set = set(mapOrd(string.printable))
rhs_set = set(mapOrd("|*)+?"))

escape_dict = dict(zip(mapOrd("nrt0\\+-()[]*|?^."), mapOrd("\n\r\t\0\\+-()[]*|?^.")))

hex_dict = dict(zip(mapOrd("0123456789abcdefABCDEF"), [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,10,11,12,13,14,15]))


class ReOneOf:
    def __init__(self, chars):
        self.chars = chars
    def visit(self, visitor):
        return visitor.visitOneOf(self.chars)

class ReEmpty:
    def __init__(self):
        pass
    def visit(self, visitor):
        return visitor.visitEmpty()

class ReConcat:
    def __init__(self, left, right):
        self.left = left
        self.right = right
    def visit(self, visitor):
        return visitor.visitConcat(self.left, self.right)

class ReChoice:
    def __init__(self, left, right):
        self.left = left
        self.right = right
    def visit(self, visitor):
        return visitor.visitChoice(self.left, self.right)

class ReRepeat:
    def __init__(self, re):
        self.re = re
    def visit(self, visitor):
        return visitor.visitRepeat(self.re)

class ParseError(Exception):
    def __init__(self, index, msg):
        self.index = index
        self.msg = msg
    def __str__(self):
        return "at {0}: {1}".format(self.index, self.msg)

class ParseRE:
    def __init__(self, s):
        self.s = s
        self.i = 0
    def do(self):
        re = self.parse_re(0)
        if self.i < len(self.s):
            self.error("Extra characters")
        return re

    def parse_group(self):
        chars = set()
        inv = False
        if self.peek() == ord('^'):
            self.take()
            inv = True

        flag = True
        lhs = None
        expectRhs = False

        while flag:
            ch = self.peek()
            if ch == ord('-'):
                self.take()
                if expectRhs or lhs == None:
                    self.error("Misplaced '-'")
                else:
                    expectRhs = True
            elif ch == ord('\\'):
                self.take()
                ch = self.parse_esc()
                if expectRhs:
                    for k in xrange(lhs, ch + 1):
                        chars.add(k)
                    lhs = None
                    expectRhs = False
                elif lhs <> None:
                    chars.add(lhs)
                    lhs = ch
                else:
                    lhs = ch
            elif ch == ord(']'):
                flag = False
            elif ch == -1:
                flag = False
            else:
                self.take()
                if expectRhs:
                    for k in xrange(lhs, ch + 1):
                        chars.add(k)
                    lhs = None
                    expectRhs = False
                elif lhs <> None:
                    chars.add(lhs)
                    lhs = ch
                else:
                    lhs = ch
              
        if expectRhs:
            self.error("Expected char after '-'")
        elif lhs <> None:
            chars.add(lhs)

        if inv:
            nchars = set()
            for k in xrange(0, 256):
                if k not in chars:
                    nchars.add(k)
            chars = nchars

        return ReOneOf(chars)

               
    def parse_esc(self):
        ch = self.peek()
        if ch in escape_dict:
            self.take()
            return escape_dict[ch]
        elif ch == ord('x'):
            self.take()
            high = self.take()
            low = self.take()
            if (high not in hex_dict) or (low not in hex_dict):
                self.error("Invalid escape sequence")
            ch = hex_dict[high] * 16 + hex_dict[low]
            return ch
        else:
            self.error("Invalid escape sequence")

    def parse_re(self, level):
        ch = self.peek()
        re = None
        if ch in rhs_set:
            return re
        elif ch == ord('.'):
            self.take()
            re = ReOneOf(range(0, 256))
        elif ch == ord('('):
            self.take()
            re = self.parse_re(0)
            if self.take() <> ord(')'):
                self.error("Expected ')'")
        elif ch == ord('\\'):
            self.take()
            re = ReOneOf([self.parse_esc()])
        elif ch == ord('['):
            self.take()
            re = self.parse_group()
            if self.take() <> ord(']'):
                self.error("Expected ']'")
        elif ch in printable_set:
            self.take()
            re = ReOneOf([ch])
        elif ch == -1:
            return None
        else:
            self.error("Unexpected character '{0}'".format(ch))
            
        flag = True
        while flag:
            ch = self.peek()
            if ch == ord('*'):
                self.take()
                re = ReRepeat(re)
            elif ch == ord('+'):
                self.take()
                re = ReConcat(re, ReRepeat(re))
            elif ch == ord('?'):
                self.take()
                re = ReChoice(re, ReEmpty())
            elif ch == ord('|') and level == 0:
                self.take()
                rhs = self.parse_re(1)
                if rhs == None:
                    rhs = ReEmpty()
                re = ReChoice(re, rhs)
            else:
                rhs = self.parse_re(1)
                if rhs <> None:
                    re = ReConcat(re, rhs)
                else:
                    flag = False

        return re

    def peek(self):
        if len(self.s) <= self.i:
            return -1
        else:
            return ord(self.s[self.i])

    def take(self):
        ch = self.peek()
        self.i = self.i + 1
        return ch
        
    def error(self, s):
        raise ParseError(self.i, s)
    
