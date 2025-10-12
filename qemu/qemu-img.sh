#!/bin/bash

qcow2_create()
{
	# Create qcow2 image
	qemu-img create -f qcow2 test.qcow2 100G
}

raw_create()
{
	qemu-img create -f raw test.raw 100G
}

qcow2_convert()
{
	qemu-img convert -O qcow2 input.qcow2 new.qcow2
}

raw_convert()
{
	qemu-img convert -O raw input.raw new.raw
}

raw2qcow2()
{
	qemu-img convert -f raw -O qcow2 disk.raw disk.qcow2
}

# Write qcow2 to target disk
qcow2_ironic_deployer()
{
	local target_disk_dev=/dev/vdb
	local src_qcow2=a.qcow2

	sudo wipefs --force --all ${target_disk_dev}

	# Get size of disk
	sudo blockdev --getsz ${target_disk_dev}

	# Zero
	sudo dd bs=512 if=/dev/zero of=${target_disk_dev} count=33
	sudo dd bs=512 if=/dev/zero of=${target_disk_dev} count=33 seek=419430367

	# Creating new GPT entries in memory.
	sudo sgdisk -Z ${target_disk_dev}

	sudo fuser ${target_disk_dev}
	sudo udevadm settle

	sudo qemu-img convert \
		-t directsync \
		-O host_device \
		-W ${src_qcow2} \
		${target_disk_dev}
}
