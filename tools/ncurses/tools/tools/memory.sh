#!/bin/bash
# display the memory usage
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

while true; do
	free -m | grep ^Mem | awk '{print $2, $3, $4, $5, $6, $7}'
	sleep 1
done | ${PLOTCAKE} --title 'Memory Usage' --xlabel 'Time' --ylabel 'Size(MB)' \
		-l total -l used -l free -l shared -l buff/cache -l avail \
		-o memory ${@}
