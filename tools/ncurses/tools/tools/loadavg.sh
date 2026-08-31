#!/bin/bash
# display the loadavg
#
# Usage: ./loadavg.sh [I=<secs>]
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

[[ -z ${I} ]] && I=1

while true; do
	awk '{print $1, $2, $3}' /proc/loadavg
	sleep ${I}
done | ${PLOTCAKE} --title 'Loadavg' --xlabel 'Time' --ylabel 'Load' \
		-l 'Load1' -l 'Load5' -l 'Load15' \
		-L unicode-boldbold -L unicode-bold -L unicode \
		-C red -C blue -C white -o loadavg ${@}
