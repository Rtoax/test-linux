#!/bin/bash
set -e

. ../../qemu/libqemu.sh

qemu_emulator=$(get_qemu_kvm_emulator)
grub_img=$PWD/grub.img
qemu_grub_img=$PWD/qemu-grub.img
boot_dir=$PWD/boot_dir.out/

dev_minor=500

goodbye()
{
	sudo umount ${boot_dir}
	sudo rmdir ${boot_dir}
	sudo rm -f ${grub_img} ${qemu_grub_img}
}
trap "goodbye" SIGINT

test_grub_with_qemu()
{
	local dev_name=loop${dev_minor}
	local dev_loop=/dev/${dev_name}


	# Do some clean first
	goodbye

	# 512MiB
	dd if=/dev/zero of=${grub_img} bs=1024 count=524288

	sudo mknod ${dev_loop} b 7 ${dev_minor}
	sudo losetup ${dev_loop} ${grub_img}

	# Add DOS partition table
	# Running:
	#  Command (m for help): o
	#  Created a new DOS disklabel with disk identifier 0x16488105.
	#
	#  Command (m for help): n
	#  Partition type
	#     p   primary (0 primary, 0 extended, 4 free)
	#     e   extended (container for logical partitions)
	#  Select (default p): p
	#  Partition number (1-4, default 1):
	#  First sector (2048-1048575, default 2048):
	#  Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-1048575, default 1048575):
	#  Created a new partition 1 of type 'Linux' and of size 511 MiB.
	#  Command (m for help): w
	sudo fdisk ${dev_loop}

	# Flush partition info
	sudo kpartx -av ${dev_loop}

	local dev_mapper_part1=/dev/mapper/${dev_name}p1
	sudo mkfs.ext4 ${dev_mapper_part1}

	mkdir -p ${boot_dir}
	sudo mount ${dev_mapper_part1} ${boot_dir}

	local target_platform=
	[[ $(uname -m) == x86_64 ]] && target_platform=i386-pc
	[[ $(uname -m) == aarch64 ]] && target_platform=arm64-efi
	sudo grub2-install \
		--root-directory=${boot_dir} \
		--no-floppy \
		--target=${target_platform} \
		${dev_loop}

	sudo qemu-img convert -O qcow2 ${grub_img} ${qemu_grub_img}

	# Running qemu...
	sudo ${qemu_emulator} -hda ${qemu_grub_img}
	# Copy kernel image to ${boot_dir}
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
	-v | --verbose)
		shift
		set -x
		;;
	-e | --err)
		shift
		set -e
		;;
	-h | --help)
		shift
		cat <<-EOF

		$0 [--minor|-h]

		--minor         device minor
		-h, --help      show this information
		-v, --verbose   show verbose, set -x
		-e, --err       set -e

		EOF
		exit 0
		;;
	*)
		break
		;;
	esac
done

test_grub_with_qemu "$@"
