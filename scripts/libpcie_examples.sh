#!/bin/bash
set -e

. libpcie.sh

pcie_nvidia_slots
pcie_intel_slots
pcie_cestc_slots

for slot in ${pcie_slots[@]}
do
	pcie_slot_to_numa ${slot}
done
