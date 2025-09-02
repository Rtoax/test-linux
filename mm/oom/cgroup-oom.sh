#!/bin/bash
set -e

readonly pid=$$
readonly CGROUP_NAME=oom-test

[[ -z ${OOMer} ]] && OOMer=oom_minimal

cleanup() {
	printf "\n"
	sudo rmdir /sys/fs/cgroup/${CGROUP_NAME}/
}
trap cleanup EXIT

sudo mkdir -p /sys/fs/cgroup/${CGROUP_NAME}/
echo ${pid} | sudo tee /sys/fs/cgroup/${CGROUP_NAME}/cgroup.procs
echo $((1024*1024*2)) | sudo tee /sys/fs/cgroup/${CGROUP_NAME}/memory.max
echo $((1024*1024*2)) | sudo tee /sys/fs/cgroup/${CGROUP_NAME}/memory.high

eval ./${OOMer} ${@}
