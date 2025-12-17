#!/bin/bash
set -e

. ../../driver/pcie/libpcie.sh

printf "%-16s %-4s\n" "PCI_SLOT" "NUMA"
for slot in $(pcie_nvidia_slots)
do
	numa=$(pcie_slot_to_numa ${slot})
	printf "%-16s %-4s\n" ${slot} ${numa}
done
