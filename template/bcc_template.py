#!/usr/bin/env python
#
# task_struct address - Get task_struct virtual address
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2022-08-20    Rong Tao    Create this.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.containers import filter_by_containers
from bcc.utils import printb
import argparse
import os
from time import strftime

bpf_text = """
#include <linux/sched.h>

struct my_data {
    unsigned long addr_task;
    unsigned long addr_se;
};

BPF_PERF_OUTPUT(sched_fork_events);

int trace_sched_fork_entry(struct pt_regs *ctx)
{
    int ret = PT_REGS_RC(ctx);

    struct my_data data = {};
    struct task_struct *task = (struct task_struct *)PT_REGS_PARM1(ctx);

    data.addr_task = (unsigned long)task;
    data.addr_se = (unsigned long)&task->se;

    sched_fork_events.perf_submit(ctx, &data, sizeof(data));

    return 0;
}

"""

def print_sched_fork_event(cpu, data, size):
    event = b["sched_fork_events"].event(data)
    printb(b"sched_fork: %-8s %lx %lx" %
           (strftime("%H:%M:%S").encode('ascii'), event.addr_task, event.addr_se))

b = BPF(text=bpf_text)
b.attach_kprobe(event="sched_fork", fn_name="trace_sched_fork_entry")

print("Tracing sched_fork ... Hit Ctrl-C to end")
b["sched_fork_events"].open_perf_buffer(print_sched_fork_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
