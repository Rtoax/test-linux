#!/bin/bash
set -e

blks=( $(ls /sys/block/) )

for b in ${blks[@]}
do
	scheduler=/sys/block/${b}/queue/scheduler
	if [[ ${b} == zram* ]]; then
		continue
	fi
	printf "%-16s : " ${b}
	cat ${scheduler}
done
