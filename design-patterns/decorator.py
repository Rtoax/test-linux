#!/bin/env python
""" Decorator 装饰模式 """

class C:
    def op(self):
        return "base"
class D:
    def __init__(self, c):
        self.c = c
    def op(self):
        return "decorated(" + self.c.op() + ")"

print(D(C()).op())  # decorated(base)
