#!/bin/env python

import cupy as cp

print("Is GPU[cuda] available? ->", cp.cuda.is_available())
if cp.cuda.is_available():
    print("cupy version ", cp.__version__)
    print("device count ", cp.cuda.runtime.getDeviceCount())
