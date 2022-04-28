#!/bin/bash

# Trace only major pagefaults:
sudo perf trace --no-syscalls -F

# Trace syscalls, major and minor pagefaults:
sudo perf trace -F all

# Trace the first minor page fault when running a workload:
sudo perf trace -F min --max-stack=7 --max-events 1 sleep 1
