#!/bin/env python
# Copyright (C) 2025 Rong Tao

import argparse
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib
import os
import sys


description = """Plot 3D with python matplotlib
"""

examples = """examples:
    ./plot.py -T a.txt b.txt
    ./plot.py -T a.txt b.txt -1
"""

parser = argparse.ArgumentParser(
    description=description,
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-T", "--txt", nargs='*', help="specify the text files.")
parser.add_argument("-x", "--xlabel", default="IOSize (KB)", help="specify x coordinate axes label")
parser.add_argument("-y", "--ylabel", default="Threads", help="specify y coordinate axes label")
parser.add_argument("-z", "--zlabel", default="Throughput (GiB/s)", help="specify z coordinate axes label")
parser.add_argument("-1", "--one", action="store_true", help="plot all in one figure")

args = parser.parse_args()

config_txt = args.txt

xlabel = args.xlabel
ylabel = args.ylabel
zlabel = args.zlabel

basic_colors = [
    'blue', 'red', 'green', 'cyan', 'magenta', 'yellow', 'black', 'white',
    'orange', 'purple', 'brown', 'pink', 'gray', 'olive', 'navy', 'teal'
]

def load_data(filename="test_data.txt"):
    data = np.loadtxt(filename, comments='#')
    x = data[:, 0]  # IOSize
    y = data[:, 1]  # Threads
    z = data[:, 2]  # Bandwidth

    print(f"Load from {filename}  {len(x)} points")
    return x, y, z


def plot_3d(fig, ax, x, y, z, title = "plot", type = 2, color = 'blue'):
    """Plot scatter"""

    # 创建网格数据
    xi = np.linspace(min(x), max(x), 50)
    yi = np.linspace(min(y), max(y), 50)
    xi, yi = np.meshgrid(xi, yi)
    # 使用插值创建网格化的z值
    from scipy.interpolate import griddata
    zi = griddata((x, y), z, (xi, yi), method='cubic')

    # Create scatter
    if type == 0:
        scatter = ax.scatter(x, y, z, c=z, cmap='viridis', s=30, alpha=0.8)
        ax.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax.set_title(title, fontsize=12, pad=15)
        plt.colorbar(scatter, ax=ax, shrink=0.5, label='Throughput (G/s)')
    # 创建曲面图（需要网格化数据）
    elif type == 1:
        # 绘制曲面
        surf = ax.plot_surface(xi, yi, zi, cmap='plasma',
                               alpha=0.8, linewidth=0, antialiased=True)
        ax.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax.set_title(title, fontsize=12, pad=15)
        fig.colorbar(surf, ax=ax, shrink=0.5, label='Throughput (G/s)')
    # 创建线框图
    elif type == 2:
        wire = ax.plot_wireframe(xi, yi, zi, rstride=3, cstride=3,
                                  color=color, alpha=0.6, linewidth=0.9)
        ax.scatter(x, y, z, color=color, s=10, alpha=0.5)
        ax.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax.set_title(title, fontsize=12, pad=15)
    # 创建等高线投影图
    elif type == 3:
        cont = ax.contour(xi, yi, zi, 20, cmap='hot',
                           offset=np.min(zi) - 1, linewidths=0.9)
        surf2 = ax.plot_surface(xi, yi, zi, cmap='viridis',
                                alpha=0.7, linewidth=0)
        ax.set_xlabel(xlabel, fontsize=10, labelpad=10)
        ax.set_ylabel(ylabel, fontsize=10, labelpad=10)
        ax.set_zlabel(zlabel, fontsize=10, labelpad=10)
        ax.set_title(title, fontsize=12, pad=15)


def fig_add_data(fig, ax, txt="test_data.txt", type = 2, color = 'blue', fignum = 1):
    if not os.path.exists(txt):
        print("Not found {txt}")
        exit()

    x, y, z = load_data(txt)

    print("\nData statistic:")
    print(f"IOSize: {min(x):.2f} - {max(x):.2f} KB")
    print(f"Threads: {min(y)} - {max(y)}")
    print(f"Throughput: {min(z):.4f} - {max(z):.4f} G/s")
    print(f"Avg Throughput: {np.mean(z):.4f} G/s")

    plot_3d(fig, ax, x, y, z, txt, type, color)


if not config_txt or len(config_txt) == 0:
    print("ERROR: Must input txt.")
    exit()

if args.one:
    fig = plt.figure(0)
    ax = fig.add_subplot(projection='3d')
    for i, a in enumerate(config_txt):
        fig_add_data(fig, ax, txt=a, color=basic_colors[i], fignum=0)
else:
    for i, a in enumerate(config_txt):
        fig = plt.figure(i)
        ax = fig.add_subplot(projection='3d')
        fig_add_data(fig, ax, txt=a, color=basic_colors[0], fignum=i)

try:
    plt.tight_layout()
    plt.show()
except KeyboardInterrupt:
    print("exit")
    exit()
