#!/bin/bash

# 记录 xfs_readdir 事件
# sudo perf list tracepoint
sudo perf trace -e xfs:xfs_readdir/nr=10/
