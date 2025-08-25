#!/bin/env python
# Gradient Descent
# Gradient descent is a simple algorithm for finding the minimum of a function
# of multiple variables. It works on the principle of looking at the local
# gradient of a function then then moving in the direction where it decreases
# the fastest.
#
# f(x), x=(x0, x1, x2, xN-1)
#
# ∂f/∂x = (∂f/∂x0, ∂f/x1, ...)
#

import numpy as np
import matplotlib.pyplot as plt

# The Rosenbrock function or the banana function is a very difficult problem
# for minimization. It has the form:
#                    f(x,y) = (a - x)^2 + b(y - x^2)^2
def rosenbrock(x0, x1, a, b):
    return (a - x0)**2 + b*(x1 - x0**2)**2

def drosdx(x, a, b):
    x0 = x[0]
    x1 = x[1]
    return np.array([-2.0*(a - x0) - 4.0*b*(x1 - x0**2)*x0,
                     2.0*b*(x1 - x0**2)])

xmin = -2.0
xmax = 2.0
ymin = -1.0
ymax = 3.0

a = 1.0
b = 100.0

N = 256
x = np.linspace(xmin, xmax, N)
y = np.linspace(ymin, ymax, N)

x2d, y2d = np.meshgrid(x, y, indexing="ij")

fig, ax = plt.subplots()

im = ax.imshow(np.log10(np.transpose(rosenbrock(x2d, y2d, a, b))),
               origin="lower", extent=[xmin, xmax, ymin, ymax])

fig.colorbar(im, ax=ax)

# TODO

plt.show()
