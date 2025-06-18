#!/bin/bash
set -e

# commit d5a21a914482 ("cxl.sh: multi memdevs to on region")
cxl_ram_4way() {
	# create region0, commit b3c049d89aa9 ("cxl: cxl.sh: create-region")
	# will create
	# - /sys/bus/cxl/devices/region0/dax_region
	# - /sys/devices/platform/ACPI0017:00/root0/decoder0.0/region0/dax_region0/dax0.0
	# - /sys/bus/dax/devices/dax0.0
	# - /sys/bus/dax/drivers/kmem/dax0.0
	# - /dev/dax0.0 [Character Device], commit 1227030c1d3f ("cxl.sh: region: character device /dev/dax0.0")
	sudo cxl create-region --decoder decoder0.0 --size 4096M --type ram --memdevs mem0 mem1 mem2 mem3

	sudo cxl enable-region region0
	sudo cxl enable-region all
	sudo cxl list --regions | jq '.[].type'

	sudo daxctl list
	sudo daxctl list -r region0

	# add memory to main RAM
	# commit 21535dd38b6e ("cxl: dax0.0: use as system-ram")
	sudo daxctl online-memory dax0.0

	# Use CXL RAM

	sudo daxctl offline-memory dax0.0

	sudo cxl disable-region region0
	sudo cxl destroy-region region0
}

# commit d61a78f78d31 ("cxl: pmem: test block device of 1way pmem")
cxl_pmem() {
	sudo cxl create-region --decoder decoder0.0 --size 1024M --type pmem --memdevs mem0
	sudo ndctl list -R

	# Create namespace, generate /dev/pmem0
	sudo ndctl create-namespace --region=region0 --mode=fsdax --size=1024M
	sudo ndctl list
	sudo lsblk

	# Use pmem block...
	# 1. dd test in VM, commit 396d70443203 ("cxl.sh: pmem: add how to use pmem block")
	test_pmem_blk {
		sudo mkfs.xfs -f /dev/pmem0
		sudo mkdir -p pmem
		sudo mount /dev/pmem0 pmem
		sudo dd if=/dev/zero of=a.bin oflag=direct bs=1M count=200 status=progress
	}

	sudo ndctl disable-namespace namespace0.0
	sudo ndctl destroy-namespace namespace0.0

	sudo ndctl disable-region region0
	sudo cxl disable-region region0
	sudo cxl destroy-region region0
}
