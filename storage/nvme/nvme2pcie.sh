#!/bin/bash
set -e

NVME=( $(ls /sys/block/ | grep 'nvme[0-9]') )
declare -a SLOT

pcie_slot_to_numa() {
	local slot=$1
	local numa=$(lspci -s ${slot} -v 2>/dev/null | \
		grep -Eo 'NUMA node [0-9]+' | grep -Eo '[0-9]+')
	if [[ -z ${numa} ]]; then
		numa='N/A'
	fi
	echo ${numa}
}

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

printf "%-16s %-16s %-4s\n" "NVME" "PCI_SLOT" "NUMA"
for ((i = 0; i < ${#NVME[@]}; i++))
do
	numa=$(pcie_slot_to_numa ${SLOT[i]})
	printf "%-16s %-16s %-4s\n" ${NVME[i]} ${SLOT[i]} ${numa}
done
