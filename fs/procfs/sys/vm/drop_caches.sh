#!/bin/bash
set -e
# Page cache
echo 1 | sudo tee /proc/sys/vm/drop_caches
# Dentry + inode
echo 2 | sudo tee /proc/sys/vm/drop_caches
# Page cache and dentry+inode
echo 3 | sudo tee /proc/sys/vm/drop_caches
