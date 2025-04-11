#!/bin/bash
set -e

huge_mnt_path="/mnt/huge"

mount_hugetlbfs()
{
	# test if dir exist
	if [[ ! -x $huge_mnt_path ]]; then
		mkdir $huge_mnt_path
	fi

	# Or add new line to /etc/fstab
	# nodev /mnt/huge hugetlbfs defaults 0 0
	# nodev /mnt/huge_1GB hugetlbfs pagesize=1GB 0 0
	mount -t hugetlbfs nodev $huge_mnt_path
	echo 20 | sudo tee /proc/sys/vm/nr_hugepages
}

umount_hugetlbfs()
{
	# TODO: can't umount hugetlbfs
	umount $huge_mnt_path
}

#
# /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
#
# On 2 NUMA System
# /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages
# /sys/devices/system/node/node1/hugepages/hugepages-2048kB/nr_hugepages
get_hugepage_info()
{
	local -a hugepage_dirs
	local -a nr_hugepages

	hugepage_dirs=( $(ls /sys/kernel/mm/hugepages/) )

	for p in ${hugepage_dirs[@]}
	do
		nr_hugepages+=( $(cat /sys/kernel/mm/hugepages/$p/nr_hugepages) )
	done

	echo -e "    SIZE \tNUM"
	for ((i = 0; i < ${#hugepage_dirs[@]}; i++))
	do
		echo -e "    ${hugepage_dirs[$i]:10}\t${nr_hugepages[$i]}"
	done
}

if [[ $(id -u) != 0 ]]; then
	echo "ERROR: Must run with root(sudo)"
	exit 1
fi

get_hugepage_info
mount_hugetlbfs
get_hugepage_info
umount_hugetlbfs
get_hugepage_info
