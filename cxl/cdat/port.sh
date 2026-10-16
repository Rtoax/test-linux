#!/bin/bash
set -e

readonly ports=( $(ls /sys/bus/cxl/devices/ | grep -Eo 'port[0-9]+') )

for port in ${ports[@]}
do
	subports=( $(ls /sys/bus/cxl/devices/${port} | grep -Eo 'port[0-9]+' || true) )
	for subport in ${subports[@]}
	do
		cdat=/sys/bus/cxl/devices/${port}/${subport}/CDAT

		if [[ ! -e ${cdat} ]]; then
			continue
		fi

		sudo cp ${cdat} ${port}-${subport}.cdat.dat
		printf "%6s/%-6s %s\n" ${port} ${subport} ${cdat}
	done
done
