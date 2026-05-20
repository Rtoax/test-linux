#!/bin/env python

class Singleton:
    _inst = None
    def __new__(cls):
        if cls._inst is None:
            cls._inst = super().__new__(cls)
        return cls._inst

print(Singleton() is Singleton())  # True
