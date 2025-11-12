#!/bin/bash

VENDOR_INTEL=8086

# -n: Show PCI vendor and device codes as numbers
slots=( $(lspci -n | awk '{print $1}') )
#  gsub: '1234:' -> '1234'
vendors=( $(lspci -n | awk '{gsub(":",""); print $2}') )


find_vendor_pci_device() {
	local vendor=$1
	# Show all intel devices
	#  -d [<vendor>]:[<device>][:<class>]
	lspci -vmm -d ${vendor}:*
	# lspci -d ${vendor}:
}

find_ether() {
	lspci -d ::0200
}

find_slot_pci_device() {
	local slot=$1
	#  -s [[[[<domain>]:]<bus>]:][<device>][.[<func>]]
	lspci -vmm -s ${slot}
}

show_tree_detail() {
	# Show tree
	lspci -t -v
}

find_vendor_pci_device ${VENDOR_INTEL}
find_slot_pci_device ${slots[1]}

