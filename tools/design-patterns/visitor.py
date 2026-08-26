#!/bin/env python
""" 访问者模式 Visitor """

class Visitor:
    def visit(self, e):
        return f"visited {e.name}"

class Element:
    def __init__(self, n):
        self.name = n
    def accept(self, v):
        return v.visit(self)

print(Element("X").accept(Visitor()))  # visited X
