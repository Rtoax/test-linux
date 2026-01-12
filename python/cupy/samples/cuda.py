#!/bin/env python

import cupy as cp

print("Is GPU[cuda] available? ->", cp.cuda.is_available())
