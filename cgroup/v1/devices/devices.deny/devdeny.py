#!/usr/bin/python3
#
# devdeny.py - check cgroup-v1 devices.deny
#
# Copyright (C) Rong Tao 2022-2025
#
# 2023-08-17    Rong Tao    Create this.
# 2023-08-18    Rong Tao    Apply log level for journal.

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
    description="Tracing cgroup-v1 devices.deny events",
    formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("-L", "--journal", action="store_true",
    help="log to systemd.journal")
parser.add_argument("-S", "--silence", action="store_true",
    help="do not print to console(stdout)")

args = parser.parse_args()
journal = args.journal
silence = args.silence

# You must do some thing.
if journal == 0 and silence:
    print("Can't set silence if no journal. see --help")
    exit()


bpf_text = """
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cgroup-defs.h>
#include <linux/kernfs.h>


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
    char cgroup_name[128];
};

BPF_PERF_OUTPUT(devcgroup_update_access_events);

int trace_devcgroup_update_access(struct pt_regs *ctx)
{
    int ret = PT_REGS_RC(ctx);

    struct my_data data = {};
    struct dev_cgroup *devcgroup = (struct dev_cgroup*)PT_REGS_PARM1(ctx);
    struct cgroup *cgroup = devcgroup->css.cgroup;
    struct kernfs_node *kernfs_node = cgroup->kn;
    const char *cgroup_name = kernfs_node->name;
    int filetype = (int)PT_REGS_PARM2(ctx);
    char *buffer = (char *)PT_REGS_PARM3(ctx);

    u32 pid = bpf_get_current_pid_tgid() >> 32;

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = pid;
    data.filetype = filetype;
    bpf_probe_read_kernel(&data.buffer, MAX_ALLOW_DENY_STR_LEN, (char *)buffer);
    bpf_probe_read_kernel(&data.cgroup_name, sizeof(data.cgroup_name), (char *)cgroup_name);

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

    # Print to stdout
    if silence == 0:
        printb(b"%-8s %-8d %-16s %-8s %-12s %-s" %
            (strftime("%H:%M:%S").encode('ascii'),
             event.pid,
             event.comm,
             filetype,
             event.buffer,
             event.cgroup_name))
    # Log to journal
    if journal:
        if event.filetype == 2: # deny
            log_func = log.warning
        else:
            log_func = log.info

        log_func(b"%s(%d) set %s/devices.%s to '%s'" %
            (event.comm,
             event.pid,
             event.cgroup_name,
             filetype,
             event.buffer))


if journal:
    log = logging.getLogger('cgroup-v1:devices.deny')
    log.addHandler(JournalHandler())
    log.setLevel(logging.INFO)
    log.info(b"sent to journal: %d" % (1))

# Main Start
b = BPF(text=bpf_text)
b.attach_kprobe(event="devcgroup_update_access", fn_name="trace_devcgroup_update_access")

if silence == 0:
    print("Tracing devices.deny ... Hit Ctrl-C to end")
    print("%-8s %-8s %-16s %-8s %-12s %-s" %
          ("TIME", "PID", "COMM", "FTYPE", "BUFFER", "CGROUP"))

b["devcgroup_update_access_events"].open_perf_buffer(print_devcgroup_update_access)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
