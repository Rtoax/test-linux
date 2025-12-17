#!/bin/bash
set -e

. libpcie.sh

find_slot_pci_device() {
	local slot=$1
	#  -s [[[[<domain>]:]<bus>]:][<device>][.[<func>]]
	lspci -vmm -s ${slot}
}

for s in $(pcie_vendor_slots ${VENDOR_NVIDIA})
do
	find_slot_pci_device $s
done
