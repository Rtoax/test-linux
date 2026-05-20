#!/bin/env python

class Leaf:
    def op(self):
        return "leaf"

class Composite:
    def __init__(self):
        self.children = []
    def add(self, c):
        self.children.append(c)
    def op(self):
        return [c.op() for c in self.children]

root = Composite()
root.add(Leaf())
root.add(Leaf())

print(root.op())  # ['leaf', 'leaf']
