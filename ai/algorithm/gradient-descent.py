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
# x <- x - η * ∂f/∂x

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

def do_descent(dfdx, x0, eps=1.e-5, eta=2.e-3, args=None, ax=None):
    # dx will be the change in the solution -- we'll iterate until this
    # is small
    dx = 1.e30
    xp_old = x0.copy()

    if args:
        grad = dfdx(xp_old, *args)
    else:
        grad = dfdx(xp_old)

    while dx > eps:

        xp = xp_old - eta * grad

        if ax:
            ax.plot([xp_old[0], xp[0]], [xp_old[1], xp[1]], color="C1")

        dx = np.linalg.norm(xp - xp_old)

        if args:
            grad_new = dfdx(xp, *args)
        else:
            grad_new = dfdx(xp)

        #eta_new = np.abs(np.transpose(xp) @ (grad_new - grad)) / np.linalg.norm(grad_new - grad)**2
        #eta = min(10*eta, eta_new)

        grad = grad_new

        xp_old[:] = xp


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

img = ax.imshow(np.log10(np.transpose(rosenbrock(x2d, y2d, a, b))),
               origin="lower", extent=[xmin, xmax, ymin, ymax])

x0 = np.array([-1.0, 1.5])
do_descent(drosdx, x0, args=(a, b), ax=ax)

fig, ax = plt.subplots()
fig.colorbar(img, ax=ax)
plt.show()
