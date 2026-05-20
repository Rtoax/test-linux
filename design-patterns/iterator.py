#!/bin/env python
""" 迭代器模式 Iterator """

class Iter:
    def __init__(self, d):
        self.d, self.i = d, 0
    def __iter__(self):
        return self
    def __next__(self):
        if self.i >= len(self.d):
            raise StopIteration
        self.i += 1
        return self.d[self.i - 1]

print(list(Iter([1, 2, 3])))  # [1, 2, 3]
