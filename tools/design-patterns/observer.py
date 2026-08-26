#!/bin/env python
""" 观察者模式 observer """

class Subject:
    def __init__(self):
        self.obs = []
    def attach(self, o):
        self.obs.append(o)
    def notify(self, v):
        [o.update(v) for o in self.obs]

class Observer:
    def update(self, v):
        print(f"got {v}")

s = Subject()

s.attach(Observer())
s.attach(Observer())

s.notify("hi")  # got hi twice
