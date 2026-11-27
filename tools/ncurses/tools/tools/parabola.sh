#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

cols=$(tput cols)
num=$((cols / 2))

for ((x = -num; x < num; x++))
do
	y=$((x * x))
	echo "(${x}, ${y}) (${x}, -${y})"
	sleep 0.02
done | ${PLOTCAKE} --title "Parabola" \
	-l "y=x^2" \
	-l "y=-x^2" \
	-o parabola "${@}"
