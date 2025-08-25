#!/bin/env python

import numpy as np
import matplotlib.pyplot as plt

x = np.array([[0, 1, 2, 3],
              [0, 1, 2, 3],
              [0, 1, 2, 3],
              [0, 1, 2, 3]])
y = np.array([[0, 0, 0, 0],
              [1, 1, 1, 1],
              [2, 2, 2, 2],
              [3, 3, 3, 3]])

plt.plot(x, y, color='r', marker='.', linestyle='')
plt.grid(True)
plt.show()
