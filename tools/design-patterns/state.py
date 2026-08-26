#!/bin/env python
""" 状态模式 State """

class Context:
    def __init__(self):
        self.state = StateA()
    def request(self):
        self.state.handle(self)

class StateA:
    def handle(self, ctx):
        ctx.state = StateB();
        print("A->B")

class StateB:
    def handle(self, ctx):
        ctx.state = StateA();
        print("B->A")

c = Context()
c.request()
c.request()  # A->B \n B->A
