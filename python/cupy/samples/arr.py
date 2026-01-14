#!/bin/env python

import cupy as cp

print("GPU[cuda] available? ", cp.cuda.is_available())

x = cp.array([1, 2, 3])
y = cp.array([4, 5, 6])

print(f'CuPy: {x + y}')
