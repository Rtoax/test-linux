#!/bin/bash
set -ex

. ../scripts/liblog.sh
. ../scripts/libnbd.sh

img_type=qcow2
img_name=test.${img_type}

nbd_dev=$(nbd_find_idle_dev)
if [[ -z ${nbd_dev} ]]; then
	error "not found valid NBD device"
fi

# Create image file and connect
sudo qemu-img create -f qcow2 ${img_name} 100G
sudo qemu-nbd --connect ${nbd_dev} ${img_name} -f ${img_type}
sudo fdisk -l ${nbd_dev}

# Make partitions
sudo fdisk -l ${nbd_dev}
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
sudo fdisk ${nbd_dev} < tmp.txt
rm tmp.txt
sudo fdisk -l ${nbd_dev}

# Create filesystem for 2 partitions
sudo mkfs.fat ${nbd_dev}p1
mkdir fat.out
sudo mount ${nbd_dev}p1 fat.out
pushd fat.out
sudo sh -c 'echo "RT is fat" > README'
popd
sudo umount fat.out
rmdir fat.out

sudo mkfs.ext4 ${nbd_dev}p2
mkdir ext4.out
sudo mount ${nbd_dev}p2 ext4.out
pushd ext4.out
sudo sh -c 'echo "RT is ext4" > README'
popd
sudo umount ext4.out
sudo rmdir ext4.out

# Disconnect nbd
sudo qemu-nbd --disconnect ${nbd_dev}

if [[ ${#BUSY_NBD_DEV[@]} -eq 0 ]]; then
	sudo rmmod nbd
fi
