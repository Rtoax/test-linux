#!/bin/env python
""" 职责链模式 Chain of Responsibility """

class Handler:
    def __init__(self, nxt=None):
        self.nxt = nxt
    def handle(self, req):
        if req == "A": return "handled by A"
        elif self.nxt: return self.nxt.handle(req)
        return "unhandled"

h = Handler(Handler())

print(h.handle("A"))  # handled by A
