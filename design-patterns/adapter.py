#!/bin/env python

class Adaptee:
    def specific(self):
        return "specific"

class Adapter:
    def __init__(self, a):
        self.a = a
    def request(self):
        return self.a.specific()

print(Adapter(Adaptee()).request())  # print: specific
