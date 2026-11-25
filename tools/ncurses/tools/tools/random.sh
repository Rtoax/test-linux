#!/bin/bash
# display the Trigonometric Functions
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

trap '' PIPE

exec 3> >(${PLOTCAKE} --title "Random" \
	-l "Random1" -l "Random2" -l "Random3" \
	-o random --x-index "${@}")

while true;
do
	echo >&3 $RANDOM $RANDOM $RANDOM
	sleep 0.02
done

exec 3>&-
wait
