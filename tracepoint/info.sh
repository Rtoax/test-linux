#!/bin/bash
set -e

# Static tracepoint
sudo cat /sys/kernel/tracing/available_events

# raw_tracepoint
# sudo bpftrace -l | grep rawtracepoint

nr_tracepoint=$(sudo bpftrace -l "tracepoint:*" | wc -l)
nr_rawtracepoint=$(sudo bpftrace -l "rawtracepoint:*" | wc -l)
nr_rawtracepoint2=$(sudo bpftrace -l "tracepoint:*" \
			| grep -v -e syscalls:sys_enter_ -e syscalls:sys_exit_ \
			| wc -l)

echo "Number tracepoint equal to ${nr_tracepoint}"
echo "Number raw_tracepoint equal to ${nr_rawtracepoint} : ${nr_rawtracepoint2}"

