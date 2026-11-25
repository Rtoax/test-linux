#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

cols=$(tput cols)
i_interval=$(( 360 / cols + 1 ))

for ((i = 0; ; i += i_interval))
do
	echo ${i} | awk '
		{
			s = sin($1 * 3.1415 / 180.0)
			c = cos($1 * 3.1415 / 180.0)
			sc = s + c
			sc2 = s - c
			sc3 = s * c
			sc4 = s * c + c
			print s" "c" "sc" "sc2" "sc3" "sc4
		}'
	sleep 0.02

	# Test enough and exit
	if [[ ${i} -eq 360000 ]]; then
		kill -INT 0
	fi
done | ${PLOTCAKE} --title "Trigonometric Functions" \
	-l "Sin" \
	-l "Cos" \
	-l "Sin+Cos" \
	-l "Sin-Cos" \
	-l "Sin*Cos" \
	-l "Sin*Cos+Cos" \
	-o trigonometric-functions --x-index "${@}"
