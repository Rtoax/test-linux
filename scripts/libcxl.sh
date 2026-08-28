#!/bin/bash
# CXL helpers
#
# Depends: jq, ndctl
#
set -e

readonly ROOTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["root decoders"][]? | .decoder') )
readonly PORTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["port decoders"][]? | .decoder') )
readonly DECODERS=( $(sudo cxl list --decoders | jq -r '.[].decoder') )
readonly ALL_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )
readonly PMEM_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[] | select(has("pmem_size")) | .memdev') )
readonly VMEM_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[] | select(has("ram_size")) | .memdev') )
# Dynamic capacity vmem device could not see "ram_size" label.
readonly OTHER_MEMDEVS=( $(sudo cxl list --memdevs | \
			jq -r '.[] | select((has("ram_size") or has("pmem_size")) | not) | .memdev') )

# $1: memdev name, like 'mem7'
cxl_memdev_size() {
	local size=$(sudo cxl list | \
		jq -r --arg dev "${1}" '.[] | select(.memdev == $dev) | (.pmem_size // .ram_size)')
	echo ${size-0}
}

cxl_info_all() {
	echo "ROOTDECODERS=\"${ROOTDECODERS[@]}\""
	echo "PORTDECODERS=\"${PORTDECODERS[@]}\""
	echo "DECODERS=\"${DECODERS[@]}\""
	echo "ALL_MEMDEVS=\"${ALL_MEMDEVS[@]}\""
	echo "PMEM_MEMDEVS=\"${PMEM_MEMDEVS[@]}\""
	echo "VMEM_MEMDEVS=\"${VMEM_MEMDEVS[@]}\""
	echo "OTHER_MEMDEVS=\"${OTHER_MEMDEVS[@]}\""

	printf "\033[1;7m%-8s %-16s\033[m\n" "MEMDEV" "SIZE"
	for dev in ${PMEM_MEMDEVS[@]} ${VMEM_MEMDEVS[@]}
	do
		printf "%-8s %-16ld\n" ${dev} $(cxl_memdev_size ${dev})
	done
}
