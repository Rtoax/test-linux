#!/usr/bin/env python
#
# task_struct address - Get task_struct virtual address
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2023-08-24    Rong Tao    Create this.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.containers import filter_by_containers
from bcc.utils import printb
import argparse
import os
from time import strftime
import logging


# arguments
parser = argparse.ArgumentParser(
    description="Add some description",
    formatter_class=argparse.RawDescriptionHelpFormatter)

args = parser.parse_args()


bpf_text = """
#include <linux/sched.h>
#include <linux/fs.h>

#define MAX_PATH_LEN    128

enum op {
    OP_OPEN,
    OP_CLOSE,
};

struct my_data {
    u32 pid;
    u32 ppid;
    char comm[TASK_COMM_LEN];
    char pcomm[TASK_COMM_LEN];
    char path[MAX_PATH_LEN];
    enum op op;
};

BPF_PERF_OUTPUT(file_events);

static int file_event(struct pt_regs *ctx, struct path *path, enum op op)
{
    u32 pid = bpf_get_current_pid_tgid() >> 32;
    struct my_data data = {};

    struct task_struct *task = (struct task_struct *)bpf_get_current_task();;
    struct task_struct *parent;
    bpf_probe_read(&parent, sizeof(parent), &task->real_parent);
    bpf_probe_read(&data.ppid, sizeof(data.ppid), &parent->pid);
    bpf_probe_read(&data.pcomm, sizeof(data.pcomm), parent->comm);

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = pid;
    data.op = op;

    bpf_d_path(path, data.path, MAX_PATH_LEN);

    file_events.perf_submit(ctx, &data, sizeof(data));

    return 0;
}

/* TODO: open,create,remove */

KFUNC_PROBE(filp_close, struct file *file)
{
    return file_event((void *)ctx, &file->f_path, OP_CLOSE);
}

"""

def handle_event(cpu, data, size):
    event = b["file_events"].event(data)
    if event.op == 0: # Open
        operate = b'OPEN'
    elif event.op == 1: # Close
        operate = b'CLOSE'

    printb(b"%-8s %-8d %-16s %-8d %-16s %-8s %-16s" %
           (strftime("%H:%M:%S").encode('ascii'),
            event.ppid,
            event.pcomm,
            event.pid,
            event.comm,
            operate,
            event.path))


b = BPF(text=bpf_text)
if BPF.support_kfunc():
    print("Use kfunc")
else:
    print("Unsupport kfunc")
    exit()

print("Tracing file event ... Hit Ctrl-C to end")
print("%-8s %-8s %-16s %-8s %-16s %-16s" %
      ("TIME", "PID", "PCOMM", "PID", "COMM", "FILE"))

b["file_events"].open_perf_buffer(handle_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
