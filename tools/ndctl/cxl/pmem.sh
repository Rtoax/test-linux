#!/bin/bash
set -e

# one of 'raw', 'fsdax', 'devdax'
declare MODE=fsdax

# commit 31a30fb65f93 ("cxl.sh: pmem: create-region")
sudo cxl create-region --decoder decoder0.0 --size 1024M --type pmem --memdevs mem0
# commit ad01a8c86ce9 ("cxl.sh: pmem: create-region 4 ways")
sudo cxl create-region --decoder decoder0.0 --size 4096M --type pmem --memdevs mem0 mem1 mem2 mem3

sudo ndctl list --regions
sudo cxl list --regions

# Create namespace, generate /dev/pmem0
# mode: raw, sector, fsdax, devdax
# - raw: /dev/pmemN (block device), commit df86a43c93e1 ("cxl: pmem: test 'raw' mode (same as fsdax)")
#   see also 'fsdax'
# - fsdax: /dev/pmemN (block device), commit d61a78f78d31 ("cxl: pmem: test block device of 1way pmem")
# - devdax: /dev/daxN.M (char device), commit 62cb28cc8244 ("cxl: devdax: create, list and test /dev/dax0.0")
#   1. mmap(2): commit 1a630215e445 ("cxl: pmem: test --mode=devdax")
#   2. libpmem
sudo ndctl create-namespace --region=region0 --mode=${MODE} --size=1024M

# note: Create namespace cost times...
# - fsdax: commit 420bc938ad4d ("cxl: cxl.sh: list namespaces of pmem fsdax")
# - devdax: commit 76d9850c67bf ("cxl: cxl.sh: list namespaces of pmem devdax")
sudo ndctl list --regions --namespaces

# Use pmem block (raw, fsdax)...
# 1. dd test in VM
#    commit 396d70443203 ("cxl.sh: pmem: add how to use pmem block")
#    commit 6b4e95c05687 ("cxl.sh: pmem: vm: why CXL pmem block is so slow in VM")
test_pmem_raw_and_fsdax() {
	local mnt=pmem

	sudo lsblk -o +fstype

	sudo mkfs.xfs -f /dev/pmem0
	sudo mkdir -p ${mnt}
	sudo mount /dev/pmem0 ${mnt}
	pushd ${mnt}
	sudo dd if=/dev/zero of=a.bin oflag=direct bs=1M count=200 status=progress
	popd
	sudo umount ${mnt}
	sudo rmdir ${mnt}
}

# Use pmem devdax
test_pmem_devdax() {
	# commit d7a71735021b ("cxl: pmem.sh: mode=devdax: daxctl list")
	sudo daxctl list --regions --devices
	# Test with mmap(2), libpmem

	# reconfigure
	sudo daxctl reconfigure-device --mode=system-ram --force dax0.0
}

sudo ndctl disable-namespace namespace0.0
sudo ndctl destroy-namespace namespace0.0

sudo ndctl disable-region region0
sudo cxl disable-region region0
sudo cxl destroy-region region0

sudo ndctl list --regions --namespaces
