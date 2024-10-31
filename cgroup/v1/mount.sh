#!/bin/bash
set -e

NAME=test-cgroupv1-$(mktemp -u XXXX)
MNT_POINT=$PWD/cgroup-v1.dir

sudo mkdir -p ${MNT_POINT}
sudo mount -t cgroup -o none,name=${NAME} ${NAME} ${MNT_POINT}

sudo mkdir -p ${MNT_POINT}/freezer
sudo mount -t cgroup -o freezer ${NAME}-freezer ${MNT_POINT}/freezer

# Show some information
mount | grep ${NAME}
findmnt
