#!/bin/bash

mkdir cgroup-v1.dir
sudo mount -t cgroup -o none,name=cgroup cgroup $PWD/cgroup-v1.dir
