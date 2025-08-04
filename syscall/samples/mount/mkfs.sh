#!/bin/bash
set -e

sudo dd if=/dev/zero of=fs.ext4 bs=1M count=2
sudo mkfs.ext4 fs.ext4
