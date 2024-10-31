#!/bin/bash
set -e

mkdir $PWD/cgroup-v2.dir
sudo mount -t cgroup2 none $PWD/cgroup-v2.dir

