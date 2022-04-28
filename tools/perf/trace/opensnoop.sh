#!/bin/bash

# Tracing open
sudo perf trace -e "open*" --syscalls

# 直接使用 syscalls:sys_enter_open
sudo perf trace -e "syscalls:sys_enter_open*"
