#!/bin/bash

# Sample CPUs at 49 Hertz, and show top addresses and symbols, live (no perf.data file):
perf top -F 49

# Sample CPUs at 49 Hertz, and show top process names and segments, live:
perf top -F 49 -ns comm,dso

# Trace system calls by process, showing a summary refreshing every 2 seconds:
perf top -e raw_syscalls:sys_enter -ns comm

# Trace sent network packets by on-CPU process, rolling output (no clear):
stdbuf -oL perf top -e net:net_dev_xmit -ns comm | strings

# -U, --hide_user_symbols: Hide user symbols.
sudo perf top --call-graph graph -U

# -K, --hide_kernel_symbols: Hide kernel symbols.
sudo perf top --call-graph graph -p 1 -K
