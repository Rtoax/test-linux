#!/bin/bash

# dump 转储- 显示汇编
# xlated
# ID 
sudo bpftool prog dump xlated id 2630
# 我的一个例子
#   0: (79) r7 = *(u64 *)(r1 +112)
#  [...]
#  27: (b7) r0 = 0
#  28: (95) exit

# visual - 更直观
sudo bpftool prog dump xlated id 2630 visual
