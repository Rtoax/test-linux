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
import logging
from systemd.journal import JournalHandler


# arguments
parser = argparse.ArgumentParser(
    description="Add some description",
    formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("-L", "--journal", action="store_true",
    help="log to systemd.journal")

args = parser.parse_args()
journal = args.journal


bpf_text = """
#include <linux/sched.h>

struct my_data {
    u32 pid;
    u32 ppid;
    char comm[TASK_COMM_LEN];
    char pcomm[TASK_COMM_LEN];
    unsigned long addr_task;
    unsigned long addr_se;
};

BPF_PERF_OUTPUT(sched_fork_events);

int trace_sched_fork_entry(struct pt_regs *ctx)
{
    int ret = PT_REGS_RC(ctx);

    u32 pid = bpf_get_current_pid_tgid() >> 32;
    struct my_data data = {};
    struct task_struct *task = (struct task_struct *)PT_REGS_PARM1(ctx);

    struct task_struct *curtask = (struct task_struct *)bpf_get_current_task();;
    struct task_struct *parent;
    bpf_probe_read(&parent, sizeof(parent), &curtask->real_parent);
    bpf_probe_read(&data.ppid, sizeof(data.ppid), &parent->pid);
    bpf_probe_read(&data.pcomm, sizeof(data.pcomm), parent->comm);

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = pid;
    data.addr_task = (unsigned long)task;
    data.addr_se = (unsigned long)&task->se;

    sched_fork_events.perf_submit(ctx, &data, sizeof(data));

    return 0;
}

"""

def print_sched_fork_event(cpu, data, size):
    event = b["sched_fork_events"].event(data)
    printb(b"%-8s %-8d %-16s %-8d %-16s %lx %lx" %
           (strftime("%H:%M:%S").encode('ascii'),
            event.ppid,
            event.pcomm,
            event.pid,
            event.comm,
            event.addr_task,
            event.addr_se))


if journal:
    log = logging.getLogger('some.name')
    log.addHandler(JournalHandler())
    log.setLevel(logging.INFO)
    log.info("sent to journal: %d" % (1))


b = BPF(text=bpf_text)
b.attach_kprobe(event="sched_fork", fn_name="trace_sched_fork_entry")

print("Tracing sched_fork ... Hit Ctrl-C to end")
print("%-8s %-8s %-16s %-8s %-16s" %
      ("TIME", "PID", "PCOMM", "PID", "COMM"))

b["sched_fork_events"].open_perf_buffer(print_sched_fork_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
