#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

cols=$(tput cols)
i_interval=$(( 360 / cols + 1 ))

for ((i = 1; ; i += i_interval))
do
	echo ${i} | awk '
		{
			p1 = sin($1 * 3.1415 / 180.0) / ($1 * 3.1415 / 180.0)
			print p1
		}'
	sleep 0.01

	# Test enough and exit
	if [[ ${i} -eq 360000 ]]; then
		kill -INT 0
	fi
done | ${PLOTCAKE} --title "Pulse" \
	-l "sin(πt)/(πt)" \
	-o trigonometric-functions --x-index "${@}"
