#!/bin/bash
set -ex

source /etc/os-release

IMG_NAME=boot.img

EFI_ARCH=
IMG_BOOTEFI=

DEV_LOOP=

MNT_BOOT=mnt.boot
MNT_BOOT_EFI=mnt.boot.efi

case $(uname -m) in
aarch64)
	EFI_ARCH=aa64
	IMG_BOOTEFI=BOOTAA64.EFI
	;;
x86_64)
	EFI_ARCH=x64
	IMG_BOOTEFI=BOOTX64.EFI
	;;
*)
	echo "ERROR: Unknown arch $(uname -m)"
	exit 1
	;;
esac


dd if=/dev/zero of=${IMG_NAME} bs=1M count=512

# Pass -drive file=./${IMG_NAME},format=raw to qemu
mk_multi_partitions_with_fdisk()
{
	local fdisk_script=fdisk.txt
	# g: Created a new GPT disklabel
	# n: add a new partition
	# 1: partition number 1
	# 2048: First sector
	# +100M: Last sector
	# t: change a partition type
	# 1: Changed type of partition 'Linux filesystem' to 'EFI System'
	# n: add a new partition
	# 2: partition number 2
	# ' ': use default First sector
	# ' ': use default Last sector
	# w: write table to disk and exit
	cat>${fdisk_script}<<-EOF
	g
	n
	1
	2048
	+100M
	t
	1
	n
	2


	w
	EOF
	DEV_LOOP=$( sudo losetup --find --show ${IMG_NAME} )

	# FIXME: fdisk return 1, the error/warning:
	# Re-reading the partition table failed.: Invalid argument
	# The kernel still uses the old table. The new table will be used at
	# the next reboot or after you run partprobe(8) or partx(8).
	sudo fdisk ${DEV_LOOP} < ${fdisk_script} || true

	sudo losetup --detach ${DEV_LOOP}

	DEV_LOOP=$( sudo losetup --find --partscan --show ${IMG_NAME} )

	sudo mkfs.vfat ${DEV_LOOP}p1
	sudo mkfs.xfs ${DEV_LOOP}p2

	mkdir -p ${MNT_BOOT_EFI} ${MNT_BOOT}
	sudo mount ${DEV_LOOP}p1 ${MNT_BOOT_EFI}
	sudo mount ${DEV_LOOP}p2 ${MNT_BOOT}

	rm -f ${fdisk_script}
}

# Pass -cdrom ${IMG_NAME} to qemu
single_partition() {
	sudo mkfs.vfat ${IMG_NAME}
	mkdir -p ${MNT_BOOT_EFI}
	sudo mount ${IMG_NAME} ${MNT_BOOT_EFI}
}

#single_partition
mk_multi_partitions_with_fdisk

sudo mkdir -p ${MNT_BOOT_EFI}/EFI/BOOT/
sudo mkdir -p ${MNT_BOOT}/grub2/

# The following methods work fine, choise one.
grub_1() {
	sudo cp /boot/efi/EFI/BOOT/${IMG_BOOTEFI} ${MNT_BOOT_EFI}/EFI/BOOT/${IMG_BOOTEFI}
	sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/BOOT/grub${EFI_ARCH}.efi
}
grub_2() {
	sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi ${MNT_BOOT_EFI}/EFI/BOOT/boot${EFI_ARCH}.efi
}
grub_1

# Get boot partition UUID
boot_uuid=$( lsblk -o uuid ${DEV_LOOP}p2 | sed 1d )
echo "search --no-floppy --fs-uuid --set=boot ${boot_uuid}
set prefix=(\$boot)/grub2

export \$prefix
configfile \$prefix/grub.cfg
" | sudo tee ${MNT_BOOT_EFI}/EFI/BOOT/grub.cfg

sudo cp grub.cfg ${MNT_BOOT}/grub2/grub.cfg
sudo cp /boot/vmlinuz-$(uname -r) ${MNT_BOOT}/vmlinuz
sudo cp /boot/initramfs-$(uname -r).img ${MNT_BOOT}/initrd.img

[[ ${DEV_LOOP} ]] && sudo fdisk -l ${DEV_LOOP}
sudo fdisk -l ${IMG_NAME}

# Do some clean
sudo umount ${MNT_BOOT_EFI}
sudo umount ${MNT_BOOT}
[[ ${DEV_LOOP} ]] && sudo losetup --detach ${DEV_LOOP}
rmdir ${MNT_BOOT_EFI} ${MNT_BOOT}

