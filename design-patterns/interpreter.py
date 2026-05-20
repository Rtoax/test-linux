#!/bin/env python
""" 解释器模式 Interpreter """

class Expr: pass
class Num(Expr):
    def __init__(self, v):
        self.v = v
    def interp(self):
        return self.v
class Add(Expr):
    def __init__(self, l, r):
        self.l, self.r = l, r
    def interp(self):
        return self.l.interp() + self.r.interp()

print(Add(Num(2), Num(3)).interp())  # 5
