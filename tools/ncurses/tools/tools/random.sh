#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

while true;
do
	echo $RANDOM $RANDOM $RANDOM
	sleep 0.02
done | ${PLOTCAKE} --title "Random" \
	-l "Random1" -l "Random2" -l "Random3" \
	-o random --x-index "${@}"
