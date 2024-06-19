#!/bin/bash
set -ex

source /etc/os-release

EFI_ARCH=

loop=

case $(uname -m) in
aarch64)
	EFI_ARCH=aa64
	;;
x86_64)
	EFI_ARCH=x64
	;;
*)
	echo "ERROR: Unknown arch $(uname -m)"
	exit 1
	;;
esac


dd if=/dev/zero of=boot.img bs=1M count=512

# Pass -drive file=./boot.img,format=raw to qemu
multi_partitions() {
	cat>fdiskpart.txt<<-EOF
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
	loop=$( sudo losetup --find --show boot.img )

	# FIXME: fdisk return 1
	sudo fdisk ${loop} < fdiskpart.txt || true

	sudo losetup --detach ${loop}

	loop=$( sudo losetup --find --partscan --show boot.img )

	sudo mkfs.vfat ${loop}p1
	sudo mkfs.xfs ${loop}p2

	mkdir -p boot.efi.mnt boot.boot.mnt
	sudo mount ${loop}p1 boot.efi.mnt
	sudo mount ${loop}p2 boot.boot.mnt
}

# Pass -cdrom boot.img to qemu
single_partition() {
	sudo mkfs.vfat boot.img
	mkdir -p boot.efi.mnt
	sudo mount boot.img boot.efi.mnt
}

#single_partition
multi_partitions

sudo mkdir -p boot.efi.mnt/efi/boot/

sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi boot.efi.mnt/efi/boot/boot${EFI_ARCH}.efi
sudo cp grub.cfg boot.efi.mnt/efi/boot/grub.cfg

[[ ${loop} ]] && sudo fdisk -l ${loop}
sudo fdisk -l boot.img

# Do some clean
sudo umount boot.efi.mnt
sudo umount boot.boot.mnt
[[ ${loop} ]] && sudo losetup --detach ${loop}
rmdir boot.efi.mnt boot.boot.mnt
rm -f fdiskpart.txt

