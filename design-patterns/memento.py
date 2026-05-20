#!/bin/env python
""" 备忘录模式 Memento """

class Memento:
    def __init__(self, s):
        self.state = s
class Originator:
    def __init__(self):
        self.state = ""
    def set(self, s):
        self.state = s
    def save(self):
        return Memento(self.state)
    def restore(self, m):
        self.state = m.state

o = Originator()

o.set("v1"); m = o.save()
o.set("v2"); o.restore(m)

print(o.state)  # v1
