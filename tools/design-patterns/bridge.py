#!/bin/env python

class Impl:
    def op(self):
        return "impl"

class ImplA(Impl):
    def op(self):
        return "A"

class ImplB(Impl):
    def op(self):
        return "B"

class Abstraction:
    def __init__(self, impl):
        self.impl = impl
    def do(self):
        return self.impl.op()

print(Abstraction(ImplA()).do())  # A
print(Abstraction(ImplB()).do())  # B
