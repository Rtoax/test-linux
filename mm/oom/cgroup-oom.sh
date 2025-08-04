#!/bin/bash
set -e

pid=$$

cleanup() {
	printf "\n"
	sudo rmdir /sys/fs/cgroup/oom-test/
}
trap cleanup EXIT

make
sudo mkdir -p /sys/fs/cgroup/oom-test/
echo ${pid} | sudo tee /sys/fs/cgroup/oom-test/cgroup.procs
echo $((1024*1024*2)) | sudo tee /sys/fs/cgroup/oom-test/memory.max
echo $((1024*1024*2)) | sudo tee /sys/fs/cgroup/oom-test/memory.high

./oom -v $@
