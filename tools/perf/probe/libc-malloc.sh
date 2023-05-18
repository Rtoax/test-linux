#!/bin/bash

# probe malloc
sudo perf probe -x /usr/lib64/libc.so.6 --add malloc
sudo perf record -e probe_libc:malloc -aR sleep 1
sudo perf probe -x /usr/lib64/libc.so.6 --del malloc
sudo perf report --stdio

# 
sudo perf record -e probe:tcp_sendmsg -a -g -- sleep 5
