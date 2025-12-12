#!/bin/bash
set -e

NVME=( $(ls /sys/block/ | grep 'nvme[0-9]') )
declare -a SLOT

if [[ ${#NVME[@]} -eq 0 ]]; then
	echo >&2 "ERROR: not found any NVME from /sys/block/"
	exit 0
fi

for ((i = 0; i < ${#NVME[@]}; i++))
do
	SLOT+=( $(realpath /sys/block/${NVME[i]} | \
		grep -oE '[0-9a-fA-F]{4}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}\.[0-9a-fA-F]' | \
		tail -n1) )
done

printf "%-16s %-16s\n" "NVME" "PCI_SLOT"
for ((i = 0; i < ${#NVME[@]}; i++))
do
	printf "%-16s %-16s\n" ${NVME[i]} ${SLOT[i]}
done
