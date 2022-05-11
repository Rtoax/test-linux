#!/bin/bash

# probe malloc
sudo perf probe -x /lib/x86_64-linux-gnu/libc-2.15.so --add malloc
sudo perf record -e probe_libc:malloc -aR sleep 1

# 
sudo perf record -e probe:tcp_sendmsg -a -g -- sleep 5
