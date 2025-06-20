#!/bin/bash
set -e

mkdir -p blkio.mnt
sudo mount -t cgroup -o blkio none blkio.mnt
