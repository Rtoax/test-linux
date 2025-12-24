#!/bin/bash
set -e

IFLIST=( $(ls /sys/class/net/) )

for iface in ${IFLIST[@]}
do
	sudo ethtool ${iface}
done
