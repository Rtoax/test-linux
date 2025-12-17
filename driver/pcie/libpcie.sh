#!/bin/bash
set -e

VENDOR_INTEL=8086

# $1: slot, for example: 0000:bf:00.0
pcie_slot_to_numa() {
	local slot=$1
	local numa=$(lspci -s ${slot} -v 2>/dev/null | \
		grep -Eo 'NUMA node [0-9]+' | grep -Eo '[0-9]+')
	if [[ -z ${numa} ]]; then
		numa='N/A'
	fi
	echo ${numa}
}

pcie_find_ether() {
	lspci -d ::0200
}

pcie_tree_detail() {
	lspci -t -v
}
