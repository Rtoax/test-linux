#!/bin/bash
set -e

. libcxl.sh
. librun.sh

for dev in ${PMEM_MEMDEVS[@]} ${VMEM_MEMDEVS[@]} ${OTHER_MEMDEVS[@]}
do
	slot=$(cxl_memdev_slot ${dev})

	# Identify PCI devices by path through each bridge, showing the bus
	# number as well as the device number.
	dry_run sudo lspci -s ${slot} -PP

	# Be even more verbose and display everything we are able to parse,
	# even if it doesn't look  interesting  at  all (e.g., undefined memory
	# regions).
	dry_run sudo lspci -s ${slot} -vvv
done

cxl_info_all
