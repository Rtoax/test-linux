#!/bin/bash
set -e

configs=$(ls /sys/bus/pci/devices/*/config)

for config in ${configs[@]}
do
	echo "${config}"
	hexdump -C ${config}
done
