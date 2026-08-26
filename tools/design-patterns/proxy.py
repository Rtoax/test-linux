#!/bin/env python
""" 代理模式 Proxy """

class Real:
    def req(self):
        return "real"
class Proxy:
    def __init__(self):
        self.r = Real()
    def req(self):
        return f"proxy({self.r.req()})"

print(Proxy().req())  # proxy(real)
