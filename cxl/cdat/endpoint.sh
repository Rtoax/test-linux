#!/bin/bash
set -e

readonly endpoints=( $(ls /sys/bus/cxl/devices/ | grep -Eo 'endpoint[0-9]+') )

for ep in ${endpoints[@]}
do
	cdat=/sys/bus/cxl/devices/${ep}/CDAT
	sudo cp ${cdat} ${ep}.cdat.dat
	printf "%-16s %s\n" ${ep} ${cdat}
done
