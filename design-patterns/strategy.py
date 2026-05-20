#!/bin/env python
""" 策略模式 strategy """

class Context:
    def __init__(self, s):
        self.s = s
    def do(self, a, b):
        return self.s(a, b)

print(Context(lambda a,b: a + b).do(3, 2))  # 5
print(Context(lambda a,b: a - b).do(3, 2))  # 1
