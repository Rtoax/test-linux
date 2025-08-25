#!/bin/env python

import numpy as np
import matplotlib.pyplot as plt

x = np.array([0, 1, 2])
y = np.array([0, 1])

X, Y = np.meshgrid(x, y)

plt.plot(X, Y, color='r', marker='.', linestyle='')
plt.grid(True)
plt.show()
