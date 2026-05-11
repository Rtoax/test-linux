#!/bin/bash
set -ex

img_type=qcow2
img_name=test.${img_type}

# Partitions not appear in /sys/block/
ALL_NBDS=( $(ls /sys/block/ | grep nbd) )

find_valid_nbd_dev() {
	local nbd
	for nbd in ${ALL_NBDS[@]}
	do
		# Found valid nbd
		if [[ ! -e /sys/block/${nbd}/pid ]]; then
			echo ${nbd}
		fi
	done
	# Not found valid nbd
}

sudo modprobe nbd max_part=16
lsmod | grep nbd

nbd_dev=$(find_valid_nbd_dev)

# Create image file and connect
sudo qemu-img create -f qcow2 ${img_name} 100G
sudo qemu-nbd --connect /dev/${nbd_dev} ${img_name} -f ${img_type}
sudo fdisk -l /dev/${nbd_dev}

# Make partitions
sudo fdisk -l /dev/${nbd_dev}
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
sudo fdisk /dev/${nbd_dev} < tmp.txt
rm tmp.txt
sudo fdisk -l /dev/${nbd_dev}

# Create filesystem for 2 partitions
sudo mkfs.fat /dev/${nbd_dev}p1
mkdir fat.out
sudo mount /dev/${nbd_dev}p1 fat.out
pushd fat.out
sudo sh -c 'echo "RT is fat" > README'
popd
sudo umount fat.out
rmdir fat.out

sudo mkfs.ext4 /dev/${nbd_dev}p2
mkdir ext4.out
sudo mount /dev/${nbd_dev}p2 ext4.out
pushd ext4.out
sudo sh -c 'echo "RT is ext4" > README'
popd
sudo umount ext4.out
sudo rmdir ext4.out

# Disconnect nbd
sudo qemu-nbd --disconnect /dev/${nbd_dev}
sudo rmmod nbd
