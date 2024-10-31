#!/bin/bash
set -e


NAME=test-cgroupv2
MNT_POINT=$PWD/cgroup-v2.dir

mkdir -p ${MNT_POINT}

sudo mount --type cgroup2 ${NAME} ${MNT_POINT}
mount | grep ${NAME}

