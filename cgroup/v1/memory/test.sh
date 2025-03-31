#!/bin/bash
set -ex

cgroupfs=$PWD/tmp-$(mktemp -u XXXX)

mkdir -p ${cgroupfs}
# TODO: none already mounted or mount point busy
sudo mount -t cgroup none ${cgroupfs}

sudo mkdir ${cgroupfs}/memory
sudo mount -t cgroup -o memory memory ${cgroupfs}/memory

sudo mkdir ${cgroupfs}/memory/0
echo $$ | sudo tee ${cgroupfs}/memory/0/tasks

echo 4M | sudo tee ${cgroupfs}/memory/0/memory.limit_in_bytes
cat ${cgroupfs}/memory/0/memory.limit_in_bytes
cat ${cgroupfs}/memory/0/memory.usage_in_bytes
