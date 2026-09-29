#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

cols=$(tput cols)
i_interval=$(( 360 / cols + 1 ))

for ((i = 0; i <= 360; i += i_interval))
do
	echo ${i} | awk '
		{
			s = sin($1 * 3.1415 / 180.0)
			c = cos($1 * 3.1415 / 180.0)
			print s" "c
		}'
	sleep 0.002
done | ${PLOTCAKE} --title "Trigonometric Functions" -l "Sin" -l "Cos" \
	-o trigonometric-functions --x-index "${@}"
