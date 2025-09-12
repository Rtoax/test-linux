#!/bin/bash
#
# refs: https://www.cnblogs.com/zlzlnet/p/6073817.html


host_expand_qcow2()
{
	local qcow2_file=centos-stream9.qcow2
	local add_size_G=20

	qemu-img info $qcow2_file
	qemu-img resize $qcow2_file +${add_size_G}G
}

guest_check_df()
{
	 df -Th
}

guest_fdisk()
{
	local dev="/dev/vda"

	fdisk $dev
	# : p
	# : n
	# : p
	# : (default)
	# : (default)
	# : (default)
	# : t
	# : (default)
	# : 8e (linux LVM)
	# : w
}

guest_pvcreate()
{
	local dev="/dev/vda3"

	pvcreate $dev

	pvs
}

guest_extend()
{
	local dev="/dev/vda3"
	local position="cs_192" # check with vgs command
	local position2="/dev/cs_192/root"

	vgs
	#  VG     #PV #LV #SN Attr   VSize   VFree
	#  cs_192   1   3   0 wz--n- 464.17g    0

	vgextend $position $dev

	vgs

	lvextend -l +100%FREE $position2

	# This may be error in 'xfs', use xfs_growfs instead
	resize2fs $position2

	xfs_growfs $position2

	df -Th
}

