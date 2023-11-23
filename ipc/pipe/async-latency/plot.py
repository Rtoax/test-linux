#!/bin/env python3

import matplotlib.pyplot as plt
from scipy import interpolate
import numpy as np
import matplotlib.font_manager as mpt

file = 'record.txt'
a = np.loadtxt(file)
x = a[:,0]
y = a[:,1]
tck = interpolate.splrep(x, y)
xx = np.linspace(min(x), max(x), 100)
yy = interpolate.splev(xx, tck, der = 0)
print(xx)
plt.plot(x, y, 'o', xx, yy)
plt.legend(['latency', 'latency'])
plt.xlabel('size per package(bytes)')
plt.ylabel('latency(Mbps)')
plt.title('Pipe latency')
plt.savefig('out.jpg')
plt.show()

