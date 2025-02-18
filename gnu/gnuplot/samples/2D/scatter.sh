#!/bin/bash
set -e

#创建一个数据文件，例如 data.dat
echo "1 2
2 3
3 5
4 7
5 11" > data.dat

# 创建一个Gnuplot脚本文件，例如 plot_script.gp
echo "set title 'Scatter Plot'
set xlabel 'X-axis'
set ylabel 'Y-axis'
set grid
plot 'data.dat' using 1:2 with points pt 7 ps 1.5 lc rgb 'blue' title 'Data Points Set 1'" > plot_script.gp

# 使用Gnuplot运行脚本文件
gnuplot -p plot_script.gp
