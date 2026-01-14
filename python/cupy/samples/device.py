#!/bin/env python

import cupy as cp

print("Is GPU[cuda] available? ->", cp.cuda.is_available())
if cp.cuda.is_available():
    print("cupy version ", cp.__version__)
    gpu_count = cp.cuda.runtime.getDeviceCount()
    print("device count ", gpu_count)
    for gpu_id in range(gpu_count):
        device = cp.cuda.Device(gpu_id)
        print("GPU ", device)
        print("Atr ", device.attributes)
