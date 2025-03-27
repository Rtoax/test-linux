#!/bin/bash
set -ex

source /etc/os-release

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
	DEV_LOOP=$( sudo losetup --find --show boot.img )

	# FIXME: fdisk return 1, the error/warning:
	# Re-reading the partition table failed.: Invalid argument
	# The kernel still uses the old table. The new table will be used at
	# the next reboot or after you run partprobe(8) or partx(8).
	sudo fdisk ${DEV_LOOP} < fdiskpart.txt || true

	sudo losetup --detach ${DEV_LOOP}

	DEV_LOOP=$( sudo losetup --find --partscan --show boot.img )

	sudo mkfs.vfat ${DEV_LOOP}p1
	sudo mkfs.xfs ${DEV_LOOP}p2

	mkdir -p ${MNT_BOOT_EFI} ${MNT_BOOT}
	sudo mount ${DEV_LOOP}p1 ${MNT_BOOT_EFI}
	sudo mount ${DEV_LOOP}p2 ${MNT_BOOT}
}

# Pass -cdrom boot.img to qemu
single_partition() {
	sudo mkfs.vfat boot.img
	mkdir -p ${MNT_BOOT_EFI}
	sudo mount boot.img ${MNT_BOOT_EFI}
}

#single_partition
multi_partitions

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
sudo fdisk -l boot.img

# Do some clean
sudo umount ${MNT_BOOT_EFI}
sudo umount ${MNT_BOOT}
[[ ${DEV_LOOP} ]] && sudo losetup --detach ${DEV_LOOP}
rmdir ${MNT_BOOT_EFI} ${MNT_BOOT}
rm -f fdiskpart.txt

