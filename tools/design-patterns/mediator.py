#!/bin/env python
""" 中介者模式 Mediator """

class Mediator:
    def __init__(self):
        self.a = self.b = None
    def set(self, a, b):
        self.a, self.b = a, b
    def notify(self, sender, msg):
        (self.b if sender == self.a else self.a).receive(msg)

class Component:
    def __init__(self, m, name):
        self.m, self.name = m, name
    def send(self, msg):
        self.m.notify(self, msg)
    def receive(self, msg):
        print(f"{self.name} got {msg}")

m = Mediator()

c1 = Component(m, "A")
c2 = Component(m, "B")

m.set(c1, c2)
c1.send("hi")  # B got hi
c2.send("hi")  # A got hi
