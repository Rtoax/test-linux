#!/bin/bash

source /etc/os-release
EFI_ARCH=

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
sudo mkfs.vfat boot.img
mkdir -p boot.efi.mnt
sudo mount boot.img boot.efi.mnt
sudo mkdir -p boot.efi.mnt/efi/boot/

sudo cp /boot/efi/EFI/${ID}/grub${EFI_ARCH}.efi boot.efi.mnt/efi/boot/boot${EFI_ARCH}.efi
sudo cp grub.cfg boot.efi.mnt/efi/boot/grub.cfg
sudo umount boot.efi.mnt
rmdir boot.efi.mnt
