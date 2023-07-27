#!/usr/bin/env python
#
# filelock   Trace filelock events
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2023-07-26    Rong Tao    Create this.
# 2023-07-27    Rong Tao    Add tid.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.utils import printb
import argparse
import os

bpf_text = """
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/list.h>

struct data_t {
    u32 pid;
    u32 tid;
    u32 owner_pid;
    char comm[TASK_COMM_LEN];
    u32 ino;
    int ret;
};
BPF_PERF_OUTPUT(filelock_events);

struct ctx_info {
    u32 owner_pid;
};
BPF_HASH(lock_pid_map, u32);

TRACEPOINT_PROBE(filelock, flock_lock_inode) {
    unsigned long i_ino = args->i_ino;
    int ret = args->ret;

    struct file_lock *lock = args->fl;
    u32 lock_pid = lock->fl_pid;
    u32 owner_pid = 0;

    u32 pid = bpf_get_current_pid_tgid() >> 32;
    u32 tid = bpf_get_current_pid_tgid() & 0x00000000ffffffff;
    struct ctx_info *ctx_info = (void *)lock_pid_map.lookup(&pid);
    if (ctx_info == 0) {
        owner_pid = 0;
    } else {
        owner_pid = ctx_info->owner_pid;
    }

    struct data_t data = {};

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = lock_pid;
    data.tid = tid;
    data.owner_pid = owner_pid;
    data.ino = i_ino;
    data.ret = ret;

    lock_pid_map.delete(&pid);

    filelock_events.perf_submit((void *)args, &data, sizeof(data));

    return 0;
}

static inline u32 try_get_owner_pid(u32 pid, struct list_head *head) {
    u32 owner_pid = 0;

    if (!head || head == head->next) {
        owner_pid = 0;
    } else {
        struct file_lock *fl = (void *)head->next - offsetof(struct file_lock, fl_list);
        if (pid != fl->fl_pid) {
            owner_pid = fl->fl_pid;
        }
    }

    return owner_pid;
}

TRACEPOINT_PROBE(filelock, locks_get_lock_context) {
    struct file_lock_context *ctx = args->ctx;

    u32 pid = bpf_get_current_pid_tgid() >> 32;
    struct ctx_info info = {};

    info.owner_pid = 0;

    /**
     * flock_make_lock: fl->fl_pid = current->tgid;
     * flock_lock_inode: list_for_each_entry(fl, &ctx->flc_flock, fl_list)
     */
    struct list_head *head = &ctx->flc_flock;

    info.owner_pid = try_get_owner_pid(pid, head);

    lock_pid_map.update(&pid, (void *)&info);

    return 0;
}
"""

def print_filelock_event(cpu, data, size):
    event = b["filelock_events"].event(data)
    printb(b"%-8d %-8d %-16s %-8d %-16d %-8d" \
           % (event.pid,
              event.tid,
              event.comm,
              event.owner_pid,
              event.ino,
              event.ret))

b = BPF(text=bpf_text)

print("Tracing filelock ... Hit Ctrl-C to end")
print("%-8s %-8s %-16s %-8s %-16s %-8s" \
      % ("PID", "TID", "COMM", "OWN_PID", "INODE", "RESULT"))

b["filelock_events"].open_perf_buffer(print_filelock_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
