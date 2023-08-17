#!/usr/bin/env python
#
# devdeny.py - check cgroup-v1 devices.deny
#
# Copyright (C) Rong Tao 2022-2023
#
# 2023-08-17	Rong Tao	Create this.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.containers import filter_by_containers
from bcc.utils import printb
import argparse
import os


bpf_text = """
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cgroup-defs.h>


#define MAX_ALLOW_DENY_STR_LEN  11

struct dev_cgroup {
    struct cgroup_subsys_state css;
    /* more field */
};

struct my_data {
    u32 pid;
    char comm[TASK_COMM_LEN];
    int filetype;
    char buffer[MAX_ALLOW_DENY_STR_LEN];
};

BPF_PERF_OUTPUT(devcgroup_update_access_events);

int trace_devcgroup_update_access(struct pt_regs *ctx)
{
    int ret = PT_REGS_RC(ctx);

    struct my_data data = {};
    struct dev_cgroup *devcgroup = (struct dev_cgroup*)PT_REGS_PARM1(ctx);
    int filetype = (int)PT_REGS_PARM2(ctx);
    char *buffer = (char *)PT_REGS_PARM3(ctx);

    u32 pid = bpf_get_current_pid_tgid() >> 32;

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = pid;
    data.filetype = filetype;
    bpf_probe_read_kernel(&data.buffer, MAX_ALLOW_DENY_STR_LEN, (char *)buffer);

    devcgroup_update_access_events.perf_submit(ctx, &data, sizeof(data));

    return 0;
}
"""

def print_devcgroup_update_access(cpu, data, size):
    event = b["devcgroup_update_access_events"].event(data)
    filetype = b"unknown"
    if event.filetype == 1: # ALLOW
        filetype = b"allow"
    elif event.filetype == 2: # DENY
        filetype = b"deny"
    elif event.filetype == 3: # LIST
        filetype = b"list"

    printb(b"%-8d %-16s %-8s %-12s" % (event.pid, event.comm, filetype, event.buffer))

# Main Start
b = BPF(text=bpf_text)
b.attach_kprobe(event="devcgroup_update_access", fn_name="trace_devcgroup_update_access")

print("Tracing devices.deny ... Hit Ctrl-C to end")
print("%-8s %-16s %-8s %-12s" % ("PID", "COMM", "FTYPE", "BUFFER"))

b["devcgroup_update_access_events"].open_perf_buffer(print_devcgroup_update_access)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
