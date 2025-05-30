#!/bin/bash
set -ex

img_type=qcow2
img_name=test.${img_type}

sudo modprobe nbd max_part=16
lsmod | grep nbd

# Create image file and connect
sudo qemu-img create -f qcow2 ${img_name} 100G
sudo qemu-nbd --connect /dev/nbd0 ${img_name} -f ${img_type}
sudo fdisk -l /dev/nbd0

# Make partitions
sudo fdisk -l /dev/nbd0
cat >tmp.txt<<-EOF
n
p
1
2048
100M
n
p
2


w
EOF
sudo fdisk /dev/nbd0 < tmp.txt
rm tmp.txt
sudo fdisk -l /dev/nbd0

# Create filesystem for 2 partitions
sudo mkfs.fat /dev/nbd0p1
mkdir fat.out
sudo mount /dev/nbd0p1 fat.out
pushd fat.out
sudo sh -c 'echo "RT is fat" > README'
popd
sudo umount fat.out
rmdir fat.out

sudo mkfs.ext4 /dev/nbd0p2
mkdir ext4.out
sudo mount /dev/nbd0p2 ext4.out
pushd ext4.out
sudo sh -c 'echo "RT is ext4" > README'
popd
sudo umount ext4.out
sudo rmdir ext4.out

# Disconnect nbd
sudo qemu-nbd --disconnect /dev/nbd0
sudo rmmod nbd
