#!/bin/bash

# 打印 map 详情
# 先使用 bpftool map show 查看 ID
sudo bpftool map dump id 2193
