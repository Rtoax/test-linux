#!/bin/env python
""" 享元模式 flyweight """

class Flyweight:
    def __init__(self, s):
        self.s = s
    def op(self, ext):
        return f"{self.s}{ext}"

class FlyweightFactory:
    pool = {}
    def get(self, key):
        if key not in self.pool:
            self.pool[key] = Flyweight(key)
        return self.pool[key]

f = FlyweightFactory()
a = f.get("a")

print(a.op("!"))  # a!
print(a is f.get("a"))  # True
