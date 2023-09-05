#!/bin/bash

dd if=/dev/zero of=uboot.disk bs=1M count=1024

# Create GPT partition
sgdisk -n 0:0:+10M -c 0:kernel uboot.disk
sgdisk -n 0:0:0 -c 0:rootfs uboot.disk
# Check partitions
sgdisk -p uboot.disk

# Example: /dev/loop0
dev_loop=$(sudo losetup -f)

sudo losetup ${dev_loop} uboot.disk
sudo partprobe ${dev_loop}

sudo mkfs.ext4 ${dev_loop}p1
sudo mkfs.ext4 ${dev_loop}p2

mkdir p1 p2
sudo mount ${dev_loop}p1 p1
sudo mount ${dev_loop}p2 p2

# Copy files
#  p1: kernel + dtb
#  p2: rootfs

sudo umount p1 p2
rmdir p1 p2
sudo losetup -d ${dev_loop}
