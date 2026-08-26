#!/bin/env python
""" Facade 外观模式 """

class CPU:
    def start(self): return "cpu"
class Memory:
    def load(self): return "mem"
class HardDrive:
    def read(self): return "hdd"

class Computer:
    def __init__(self):
        self.cpu = CPU(); self.mem = Memory(); self.hdd = HardDrive()
    def start(self):
        return f"{self.cpu.start()} {self.mem.load()} {self.hdd.read()}"

print(Computer().start())  # cpu mem hdd
