#!/bin/bash

set -e

. config

kernel_root_dir=${LINUX_KERNEL_DIR}

dd if=/dev/zero of=uboot.disk bs=1M count=1024

# Create GPT partition
sgdisk -n 0:0:+900M -c 0:kernel uboot.disk
sgdisk -n 0:0:0 -c 0:rootfs uboot.disk
# Check partitions
sgdisk -p uboot.disk

# Example: /dev/loop0
dev_loop=$(sudo losetup -f)

sudo losetup ${dev_loop} uboot.disk
sudo partprobe ${dev_loop}

sudo mkfs.fat ${dev_loop}p1
sudo mkfs.ext4 ${dev_loop}p2

mkdir p1 p2
sudo mount ${dev_loop}p1 p1
sudo mount ${dev_loop}p2 p2

# Copy files
#  p1: kernel + dtb
#   linux: aarch64 + vexpress_defconfig
if [[ ! -z "${UBOOTDISK_PARTITION1_FILES[@]}" ]]; then
	sudo cp -a ${UBOOTDISK_PARTITION1_FILES[@]} p1/ || true
else
	echo "WARNING: not found any files"
	read -p "Press any key to continue."
fi
sudo touch p1/hello.txt

#  p2: rootfs
sudo touch p2/hello.txt

destroy() {
	sudo umount p1 p2 || true
	rmdir p1 p2 || true
	sudo losetup -d ${dev_loop} || true
}
trap destroy EXIT

echo "Success.."
