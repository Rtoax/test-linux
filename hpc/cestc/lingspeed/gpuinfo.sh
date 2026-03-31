#!/bin/bash
set -e

. ../../../driver/pcie/libpcie.sh

# Format, Number-Name-Slot:
# GPU#0  X710-M  0002:04:00.0
# GPU#1  X710-M  0002:05:00.0
N_N_S=( $(ls-smi --show-pcie | grep -E 'GPU#[0-9]+') )

printf "%-8s %-8s %-16s %-4s\n" "NUM" "NAME" "PCI_SLOT" "NUMA"
for ((i = 0; i < ${#N_N_S[@]}; i+=3))
do
	idx=$(( i / 3 ))

	num=${N_N_S[$(( idx * 3 ))]}
	name=${N_N_S[$(( idx * 3 + 1 ))]}
	slot=${N_N_S[$(( idx * 3 + 2 ))]}
	numa=$(pcie_slot_to_numa ${slot})

	printf "%-8s %-8s %-16s %-4s\n" ${num} ${name} ${slot} ${numa}
done
