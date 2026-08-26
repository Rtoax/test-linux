#!/bin/env python
""" 命令模式 Command """

class Command:
    def execute(self): pass

class Light:
    def on(self):
        return "on"
    def off(self):
        return "off"

class LightOn(Command):
    def __init__(self, l):
        self.l = l
    def execute(self):
        return self.l.on()

class LightOff(Command):
    def __init__(self, l):
        self.l = l
    def execute(self):
        return self.l.off()

print(LightOn(Light()).execute())  # on
print(LightOff(Light()).execute())  # off
