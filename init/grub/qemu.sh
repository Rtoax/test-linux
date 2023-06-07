#!/bin/bash

set -ex

qemu_emulator=/usr/libexec/qemu-kvm
grub_img=$PWD/grub.img
qemu_grub_img=$PWD/qemu-grub.img
boot_dir=$PWD/boot/

dev_minor=500

test_grub_with_qemu()
{
	local dev_name=loop${dev_minor}
	local dev_loop=/dev/${dev_name}


	# 512MiB
	dd if=/dev/zero of=${grub_img} bs=1024 count=524288

	sudo mknod ${dev_loop} b 7 ${dev_minor}
	sudo losetup ${dev_loop} ${grub_img}

	sudo fdisk ${dev_loop}
	# Add DOS partition table

	# Flush partition info
	sudo kpartx -av ${dev_loop}

	local dev_mapper_part1=/dev/mapper/${dev_name}p1
	sudo mkfs.ext4 ${dev_mapper_part1}

	mkdir -p ${boot_dir}
	sudo mount ${dev_mapper_part1} ${boot_dir}

	local target_platform=
	[[ $(uname -m) == x86_64 ]] && target_platform=x86_64-efi
	[[ $(uname -m) == aarch64 ]] && target_platform=arm64-efi
	sudo grub2-install \
		--root-directory=${boot_dir} \
		--no-floppy \
		--target=${target_platform} \
		${dev_loop}

	sudo qemu-img convert -O qcow2 ${grub_img} ${qemu_grub_img}

	sudo ${qemu_emulator} -hda ${qemu_grub_img}
	# grub>
	# grub>ls
	# (hd0)(hd0,msdos1)(fd0)
	# grub>root=(hd0,msdos1)
	# grub>linux /bzImage
	# grub>boot
}

while :; do
	case $1 in
	--minor)
		shift
		dev_minor=$1
		shift
		;;
	*)
		break
		;;
	esac
done

test_grub_with_qemu "$@"

