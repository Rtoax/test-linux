#!/bin/bash
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

for ((i = 0; i < 30; i++))
do
	if [[ $i -le 5 ]]; then
		echo 10 0 0
	elif [[ $i -ge 10 ]] && [[ $i -le 15 ]]; then
		echo 0 15 0
	elif [[ $i -ge 20 ]] && [[ $i -le 25 ]]; then
		echo 0 0 9
	else
		echo 0 0 0
	fi
	sleep 0.01
done | ${PLOTCAKE} --title 'Bar chart' -L unicode-area-chart \
		-L unicode-area-chart -L unicode-area-chart \
		-o bar-chart ${@}
