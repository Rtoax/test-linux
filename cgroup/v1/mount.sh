#!/bin/bash
set -ex

NAME=$(mktemp -u cgroupv1-XXXX)
MNT=${NAME}.mnt

sudo mkdir -p ${MNT}

cleanall() {
	sudo umount ${MNT}/memory ${MNT}/cpu,cpuacct ${MNT}/freezer ${MNT}/net_cls,net_prio ${MNT} || true
	sudo rm -rf ${MNT} || true
}
trap cleanall EXIT

sudo mount -t cgroup -o none,name=${NAME} ${NAME} ${MNT}

sudo mkdir -p ${MNT}/freezer ${MNT}/cpu,cpuacct ${MNT}/memory ${MNT}/net_cls,net_prio/

sudo mount -t cgroup -o freezer ${NAME}-freezer ${MNT}/freezer
sudo mount -t cgroup -o net_cls,net_prio ${NAME}-net ${MNT}/net_cls,net_prio/
sudo mount -t cgroup -o cpu,cpuacct cgroup ${MNT}/cpu,cpuacct
sudo mount -t cgroup -o memory ${NAME}-memory ${MNT}/memory

mount | grep ${NAME}
