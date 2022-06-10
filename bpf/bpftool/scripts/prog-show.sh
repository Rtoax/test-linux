#!/bin/bash

# 显示已经加载 的 BPF 程序
sudo bpftool prog show

# --json 格式输出
# 显示特定 ID 的程序
# jq json 格式化工具
sudo bpftool prog show --json id 52 | jq
