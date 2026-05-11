#!/bin/bash
set -ex

img_type=qcow2
img_name=test.${img_type}

# VALID_NBD_DEV: not body use this nbd device
# BUSY_NBD_DEV: nbd device already used
declare -a ALL_NBD_DEV VALID_NBD_DEV

# Auto probe nbd driver and statistic
update_nbd_devices() {
	local nbd

	# Partitions not appear in /sys/block/
	ALL_NBD_DEV=( $(ls /sys/block/ | grep nbd || true) )

	# create NBD devices
	if [[ ${#ALL_NBD_DEV[@]} -eq 0 ]]; then
		sudo modprobe nbd max_part=16
		lsmod | grep nbd
		ALL_NBD_DEV=( $(ls /sys/block/ | grep nbd || true) )
	fi

	# Reset valid NBD
	unset VALID_NBD_DEV
	unset BUSY_NBD_DEV
	for nbd in ${ALL_NBD_DEV[@]}
	do
		if [[ -e /sys/block/${nbd}/pid ]]; then
			BUSY_NBD_DEV+=( ${nbd} )
		else
			VALID_NBD_DEV+=( ${nbd} )
		fi
	done
}

find_valid_nbd_dev() {
	local nbd
	for nbd in ${ALL_NBD_DEV[@]}
	do
		# Found valid nbd
		if [[ ! -e /sys/block/${nbd}/pid ]]; then
			echo ${nbd}
			return 0
		fi
	done
	# Not found valid nbd
}

update_nbd_devices

nbd_dev=$(find_valid_nbd_dev)
if [[ -z ${nbd_dev} ]]; then
	echo >&2 "ERROR: not found valid NBD device"
	exit 1
fi

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

update_nbd_devices

if [[ ${#BUSY_NBD_DEV[@]} -eq 0 ]]; then
	sudo rmmod nbd
fi
