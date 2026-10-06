#!/bin/bash
set -e

readonly PID=$$
readonly CGROUP_NAME=oom-test
readonly SIZE_B=$((1024*1024*2))

[[ -z ${OOMer} ]] && OOMer=./oom

cleanup() {
	printf "\n"
	sudo rmdir /sys/fs/cgroup/${CGROUP_NAME}/
}
trap cleanup EXIT

# Create cgroup
echo "Creating cgroup '${CGROUP_NAME}'"
sudo mkdir -p /sys/fs/cgroup/${CGROUP_NAME}/

# Attach process to cgroup
echo "Attach process ${PID} to cgroup '${CGROUP_NAME}'"
echo ${PID} | sudo tee /sys/fs/cgroup/${CGROUP_NAME}/cgroup.procs

# Limit the memory
echo "Limiting cgroup memory to ${SIZE_B} bytes"
echo ${SIZE_B} | sudo tee /sys/fs/cgroup/${CGROUP_NAME}/memory.max
echo ${SIZE_B} | sudo tee /sys/fs/cgroup/${CGROUP_NAME}/memory.high

# OOMing
eval ${OOMer} ${@}
