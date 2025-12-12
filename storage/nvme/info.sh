#!/bin/bash
set -e

dev_nvme=( $(sudo nvme list | grep ^/dev/nvme | awk '{print $1}') )
for dev in ${dev_nvme[@]}
do
	sudo sg_inq ${dev} | sed 's/^/\t/g'
done

lspci -vmmk | grep -i nvme -A 10 -B 10
sudo nvme list
sudo grep nvme /proc/iomem
