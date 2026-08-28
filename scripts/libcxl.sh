#!/bin/bash
# CXL helpers
#
# Depends: jq, ndctl
#
set -e

readonly LIBCXL_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBCXL_ROOT}/libstring.sh

readonly ROOTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["root decoders"][]? | .decoder') )
readonly PORTDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["port decoders"][]? | .decoder') )
readonly EPDECODERS=( $(sudo cxl list --decoders | jq -r '.[] | .["endpoint decoders"][]? | .decoder') )
readonly ALL_DECODERS=( $(sudo cxl list --decoders | jq -r '.[] |
				.decoder,
				(.["root decoders"] // [] | .[]? | .decoder),
				(.["port decoders"] // [] | .[]? | .decoder),
				(.["endpoint decoders"] // [] | .[]? | .decoder) | select(. != null)') )
readonly ALL_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[].memdev') )
readonly PMEM_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[] | select(has("pmem_size")) | .memdev') )
readonly VMEM_MEMDEVS=( $(sudo cxl list --memdevs | jq -r '.[] | select(has("ram_size")) | .memdev') )
# Dynamic capacity vmem device could not see "ram_size" label.
readonly OTHER_MEMDEVS=( $(sudo cxl list --memdevs | \
			jq -r '.[] | select((has("ram_size") or has("pmem_size")) | not) | .memdev') )

# $1: memdev name, like 'mem7'
cxl_memdev_size() {
	local size=$(sudo cxl list --memdevs | \
		jq -r --arg dev "${1}" '.[] | select(.memdev == $dev) | (.pmem_size // .ram_size)')
	[[ ${size} == null ]] && size=0
	echo ${size-0}
}

# $1: memdev name, like 'mem7'
cxl_memdev_type() {
	# FIXME: may not only dynamic capacity for lost `size` label.
	local type=$(sudo cxl list --memdevs | \
		jq -r --arg dev "${1}" '
			.[] | select(.memdev == $dev) |
				if has("pmem_size") then "pmem"
				elif has("ram_size") then "ram"
				else "ram(DyCap)" end')
	echo ${type-unknown}
}

# $1: memdev name, like 'mem7'
cxl_memdev_slot() {
	local slot=$(sudo cxl list --memdevs | \
		jq -r --arg dev "${1}" '.[] | select(.memdev == $dev) | .host')
	echo ${slot-?}
}

# $1: memdev name, like 'mem7'
cxl_memdev_serial() {
	local slot=$(sudo cxl list --memdevs | \
		jq -r --arg dev "${1}" '.[] | select(.memdev == $dev) | .serial')
	echo ${slot-?}
}

# $1: memdev name, like 'mem7'
cxl_memdev_endpoint() {
	# [
	#  {
	#    "endpoint":"endpoint17",
	#    "host":"mem9",
	#    "parent_dport":"0000:17:02.0",
	#    "depth":3,
	#    "decoders_committed":0
	#  },
	#  ....
	# ]
	local slot=$(sudo cxl list --endpoints | \
		jq -r --arg dev "${1}" '.[] | select(.host == $dev) | .endpoint')
	echo ${slot-?}
}

cxl_info_all() {
	echo "ROOTDECODERS=\"${ROOTDECODERS[@]}\""
	echo "PORTDECODERS=\"${PORTDECODERS[@]}\""
	echo "EPDECODERS=\"${EPDECODERS[@]}\""
	echo "ALL_DECODERS=\"${ALL_DECODERS[@]}\""
	echo "ALL_MEMDEVS=\"${ALL_MEMDEVS[@]}\""
	echo "PMEM_MEMDEVS=\"${PMEM_MEMDEVS[@]}\""
	echo "VMEM_MEMDEVS=\"${VMEM_MEMDEVS[@]}\""
	echo "OTHER_MEMDEVS=\"${OTHER_MEMDEVS[@]}\""

	printf "\033[1;3;4;7m%-8s %-10s %-8s %-12s %-8s %-13s\033[m\n" \
	       "MEMDEV" "TYPE" "SIZE" "PCI" "SERIAL" "ENDPOINT"
	for dev in ${PMEM_MEMDEVS[@]} ${VMEM_MEMDEVS[@]} ${OTHER_MEMDEVS[@]}
	do
		printf "%-8s %-10s %-8s %-12s %-8s %-13s\n" \
			${dev} \
			$(cxl_memdev_type ${dev}) \
			$(sizeceilfmt $(cxl_memdev_size ${dev})) \
			$(cxl_memdev_slot ${dev}) \
			$(cxl_memdev_serial ${dev}) \
			$(cxl_memdev_endpoint ${dev})
	done
}
