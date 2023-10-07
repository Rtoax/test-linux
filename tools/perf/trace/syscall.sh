#!/bin/bash

# Tracing syscalls
sudo perf trace
sudo perf trace --pid=$pid
#  Show only syscalls that failed, i.e. that returned < 0
sudo perf trace --failure

# Tracing open/openat for 4 events
sudo perf trace -e open* --max-events 4
