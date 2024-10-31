#!/bin/bash
set -e

NAME=test-cgroupv1
MNT_POINT=$PWD/cgroup-v1.dir

mkdir -p ${MNT_POINT}

sudo mount -t cgroup -o none,name=${NAME} ${NAME} ${MNT_POINT}
mount | grep ${NAME}
