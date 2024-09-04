#!/bin/bash

# 有哪些追踪器可用
#  same as /sys/kernel/tracing/available_tracers
sudo trace-cmd list -t

# 用 function 启用你的第一个追踪器
sudo trace-cmd start -p function
# 启用函数调用图追踪器
sudo trace-cmd start -p function_graph
# 调整追踪以增加深度
sudo trace-cmd start -p function_graph --max-graph-depth 5

# 了解可被追踪的函数
# 例如搜索常见的内核函数 kmalloc
sudo trace-cmd list -f | grep kmalloc

# 追踪内核模块相关的函数
sudo lsmod | grep kvm_intel
sudo trace-cmd list -f | grep ']$'  | grep kvm_intel

# 追踪特定函数
sudo trace-cmd list -f | grep ^xfs_
sudo trace-cmd record -l xfs_* -p function_graph
# 追踪一个特定的 PID
#  PID=8085 为一个特定的bash，执行下面一条命令后，在8085终端执行任何命令
#  如 ls
sudo trace-cmd record -P 8085 -p function_graph
#  Hit Ctrl^C to stop recording
#  这会生成 trace.dat

# 按 event 追踪
sudo trace-cmd record -e sched -p function_graph
sudo trace-cmd record -e sched_switch -p function_graph

# 查看追踪记录
sudo trace-cmd report | head -20

# 查看追踪输出
sudo trace-cmd show | head -20

# 停止追踪并清除缓冲区
sudo trace-cmd stop
sudo trace-cmd clear

