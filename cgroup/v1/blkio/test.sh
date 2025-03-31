#!/bin/bash
set -e

sudo mount -t cgroup -o blkio none /sys/fs/cgroup/blkio

# Specify a bandwidth rate on particular device for root group. The format for
# policy is
#
#     <major>:<minor> <bytes_per_second>
#
# This will put a limit of 1MB/second on reads happening for root group on
# device having major/minor number 8:16.
echo "8:16  1048576" | sudo tee /sys/fs/cgroup/blkio/blkio.throttle.read_bps_device

# Then, test with dd.
