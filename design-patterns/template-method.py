#!/bin/env python
""" 模板方法模式 template-method """

class Base:
    def template(self):
        return self.step1() + self.step2()
class A(Base):
    def step1(self):
        return "A1"
    def step2(self):
        return "A2"

print(A().template())  # A1A2
