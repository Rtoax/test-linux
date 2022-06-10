#!/bin/bash

# 创建新的映射
sudo bpftool map create /sys/fs/bpf/counter type array key 4 value 4 entries 5 name counter
