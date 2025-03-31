#!/bin/bash
set -ex

NAME=tst-cgrp1-$(mktemp -u XXXX)
MNT_POINT=$PWD/cgroup-v1.dir

sudo mkdir -p ${MNT_POINT}
sudo mount -t cgroup -o none,name=${NAME} ${NAME} ${MNT_POINT}

cleanall() {
	#sudo tree ${MNT_POINT} || true
	sudo umount ${MNT_POINT}/cpuacct ${MNT_POINT}/freezer ${MNT_POINT} || true
	sudo rm -rf ${MNT_POINT} || true
}
trap cleanall EXIT

mount_freezer() {
	sudo mkdir -p ${MNT_POINT}/freezer
	sudo mount -t cgroup -o freezer ${NAME}-freezer ${MNT_POINT}/freezer
}
mount_freezer

mount_cpuacct() {
	sudo mkdir -p ${MNT_POINT}/cpuacct
	sudo mount -t cgroup -o cpuacct none ${MNT_POINT}/cpuacct
}
mount_cpuacct

mount_memory() {
	sudo mkdir -p ${MNT_POINT}/memory
	sudo mount -t cgroup -o memory ${NAME}-memory ${MNT_POINT}/memory
}
mount_memory

# Show some information
mount | grep ${NAME}
findmnt
