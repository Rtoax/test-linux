#!/bin/bash
set -e

configs=$(ls /sys/bus/pci/devices/*/config)
slots=$(ls /sys/bus/pci/devices/)

for config in ${configs[@]}
do
	./parse --config-file ${config}
done

for slot in ${slots[@]}
do
	./parse --slot ${slot}
done
