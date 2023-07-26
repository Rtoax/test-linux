#!/usr/bin/env python
#
# filelock   Trace filelock events
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2023-07-26    Rong Tao    Create this.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.utils import printb
import argparse
import os

bpf_text = """
#include <linux/fs.h>
#include <linux/sched.h>

struct data_t {
    u32 pid;
    char comm[TASK_COMM_LEN];
    u32 ino;
    int ret;
};
BPF_PERF_OUTPUT(filelock_events);

TRACEPOINT_PROBE(filelock, flock_lock_inode) {
    unsigned long i_ino = args->i_ino;
    int ret = args->ret;

    u32 pid = bpf_get_current_pid_tgid() >> 32;
    struct data_t data = {};

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = pid;
    data.ino = i_ino;
    data.ret = ret;

    filelock_events.perf_submit((void *)args, &data, sizeof(data));

    return 0;
}
"""

def print_filelock_event(cpu, data, size):
    event = b["filelock_events"].event(data)
    printb(b"%-8d %-16s %-8d %-8d" \
           % (event.pid, event.comm, event.ino, event.ret))

b = BPF(text=bpf_text)

print("Tracing filelock ... Hit Ctrl-C to end")
print("%-8s %-16s %-8s %-8s" % ("PID", "COMM", "INODE", "RESULT"))

b["filelock_events"].open_perf_buffer(print_filelock_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
