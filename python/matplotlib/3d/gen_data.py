#!/bin/env python
import numpy as np
import os

def generate_test_data(filename="test_data.txt", num_points=200):
    """
    Generate 3D datas
    x: IOSize (KB) - Range: 1-1024KB
    y: Thread number - range: 1-32
    z: Throughput (G/s)
    """
    np.random.seed(42)
    
    x = np.random.uniform(1, 1024, num_points)
    y = np.random.randint(1, 33, num_points)
    
    noise = np.random.normal(0, 0.2, num_points)
    z = 0.5 * y + 2 * np.log(x) + noise
    z = np.abs(z)
    
    with open(filename, 'w') as f:
        f.write("# IOSize(KB) Threads Bandwidth(G/s)\n")
        for i in range(num_points):
            f.write(f"{x[i]:.2f} {y[i]} {z[i]:.4f}\n")
    
    print(f"Data saved to {filename}")
    print(f"Points: {num_points}")
    
    return x, y, z

x_data, y_data, z_data = generate_test_data()

print("\nShow 10 of datas:")
print("IOSize(KB) | Threads | Bandwidth(G/s)")
print("-" * 35)
for i in range(10):
    print(f"{x_data[i]:10.2f} | {y_data[i]:8} | {z_data[i]:10.4f}")
