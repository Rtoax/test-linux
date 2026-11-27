#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

for ((x = -100; x < 100; x++))
do
	y=$((x * x))
	echo "(${x}, ${y}) (${x}, -${y})"
	sleep 0.02
done | ${PLOTCAKE} --title "Parabola" \
	-l "y=x^2" \
	-l "x=y^2" \
	-o parabola "${@}"
