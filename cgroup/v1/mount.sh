#!/bin/bash
set -ex

NAME=$(mktemp -u cgroupv1-XXXX)
MNT=${NAME}.mnt

sudo mkdir -p ${MNT}

cleanall() {
	sudo umount ${MNT}/memory ${MNT}/cpu,cpuacct ${MNT}/freezer ${MNT} || true
	sudo rm -rf ${MNT} || true
}
trap cleanall EXIT

sudo mount -t cgroup -o none,name=${NAME} ${NAME} ${MNT}

sudo mkdir -p ${MNT}/freezer ${MNT}/cpu,cpuacct ${MNT}/memory

sudo mount -t cgroup -o freezer ${NAME}-freezer ${MNT}/freezer
sudo mount -t cgroup -o cpu,cpuacct ${NAME}-cpu,cpuacct ${MNT}/cpu,cpuacct
sudo mount -t cgroup -o memory ${NAME}-memory ${MNT}/memory

mount | grep ${NAME}
