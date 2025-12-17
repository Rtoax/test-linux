#!/bin/bash
# refs:
# - https://pcisig.com/membership/member-companies
set -e

readonly VENDOR_INTEL=8086
readonly VENDOR_NVIDIA=10DE

# -n: Show PCI vendor and device codes as numbers
readonly pcie_slots=( $(lspci -n | awk '{print $1}' | sort -u ) )
#  gsub: '1234:' -> '1234'
readonly pcie_vendors=( $(lspci -n | awk '{gsub(":",""); print $2}' | sort -u) )

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

# $1: Vendor
pcie_vendor_slots() {
	local vendor=$1
	# Show all intel devices
	#  -d [<vendor>]:[<device>][:<class>]
	lspci -d ${vendor}:* 2>/dev/null | awk '{print $1}'
}

pcie_find_ether() {
	lspci -d ::0200
}

pcie_tree_detail() {
	lspci -t -v
}
