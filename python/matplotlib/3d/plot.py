#!/bin/env python
# Copyright (c) 2025 Rong Tao

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib
import os

xlabel = 'IOSize (KB)'
ylabel = 'Threads'
zlabel = 'Throughput (G/s)'


def load_data(filename="test_data.txt"):
    data = np.loadtxt(filename, comments='#')
    x = data[:, 0]  # IOSize
    y = data[:, 1]  # Threads
    z = data[:, 2]  # Bandwidth

    print(f"Load from {filename}  {len(x)} points")
    return x, y, z


def plot_3d(x, y, z, type = 2, fignum = 1):
    """Plot scatter"""

    # 创建网格数据
    xi = np.linspace(min(x), max(x), 50)
    yi = np.linspace(min(y), max(y), 50)
    xi, yi = np.meshgrid(xi, yi)
    # 使用插值创建网格化的z值
    from scipy.interpolate import griddata
    zi = griddata((x, y), z, (xi, yi), method='cubic')

    if type == 0:
        # Create scatter
        fig = plt.figure(fignum)
        ax1 = fig.add_subplot(projection='3d')
        scatter = ax1.scatter(x, y, z, c=z, cmap='viridis', s=30, alpha=0.8)
        ax1.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax1.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax1.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax1.set_title('Scatter3d', fontsize=12, pad=15)
        plt.colorbar(scatter, ax=ax1, shrink=0.5, label='Throughput (G/s)')
    elif type == 1:
        # 创建曲面图（需要网格化数据）
        fig = plt.figure(fignum)
        ax2 = fig.add_subplot(projection='3d')
        # 绘制曲面
        surf = ax2.plot_surface(xi, yi, zi, cmap='plasma',
                               alpha=0.8, linewidth=0, antialiased=True)
        ax2.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax2.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax2.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax2.set_title('Surface', fontsize=12, pad=15)
        fig.colorbar(surf, ax=ax2, shrink=0.5, label='Throughput (G/s)')
    elif type == 2:
        # 创建线框图
        fig = plt.figure(fignum)
        ax3 = fig.add_subplot(projection='3d')
        wire = ax3.plot_wireframe(xi, yi, zi, rstride=3, cstride=3,
                                  color='blue', alpha=0.6, linewidth=0.5)
        ax3.scatter(x, y, z, color='red', s=10, alpha=0.5)
        ax3.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax3.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax3.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax3.set_title('scatter + wireframe', fontsize=12, pad=15)
    elif type == 3:
        # 创建等高线投影图
        fig = plt.figure(fignum)
        ax4 = fig.add_subplot(projection='3d')
        cont = ax4.contour(xi, yi, zi, 20, cmap='hot',
                           offset=np.min(zi) - 1, linewidths=0.5)
        surf2 = ax4.plot_surface(xi, yi, zi, cmap='viridis',
                                alpha=0.7, linewidth=0)
        ax4.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax4.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax4.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax4.set_title('Surface + contour', fontsize=12, pad=15)


def create_figure(txt="test_data.txt", type = 2, fignum = 1):
    if not os.path.exists(txt):
        print("Not found {txt}")
        exit()

    x, y, z = load_data(txt)

    print("\nData statistic:")
    print(f"IOSize: {min(x):.2f} - {max(x):.2f} KB")
    print(f"Threads: {min(y)} - {max(y)}")
    print(f"Throughput: {min(z):.4f} - {max(z):.4f} G/s")
    print(f"Avg Throughput: {np.mean(z):.4f} G/s")

    plot_3d(x, y, z, type, fignum)


create_figure(type=2, fignum=1)
create_figure(type=0, fignum=2)

plt.tight_layout()
plt.show()
