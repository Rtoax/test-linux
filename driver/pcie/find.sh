#!/bin/bash
set -e

. libpcie.sh

# -n: Show PCI vendor and device codes as numbers
slots=( $(lspci -n | awk '{print $1}') )
#  gsub: '1234:' -> '1234'
vendors=( $(lspci -n | awk '{gsub(":",""); print $2}') )


find_slot_pci_device() {
	local slot=$1
	#  -s [[[[<domain>]:]<bus>]:][<device>][.[<func>]]
	lspci -vmm -s ${slot}
}

find_slot_pci_device ${slots[1]}
pcie_vendor_slots ${VENDOR_INTEL}
pcie_vendor_slots ${VENDOR_NVIDIA}
