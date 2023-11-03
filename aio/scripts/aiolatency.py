#!/bin/env python3
#
# aiolatency   Trace aio submit-getevent event latency
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2023-11-03    Rong Tao    Create this.

from bcc import BPF
from bcc.utils import printb
from time import strftime
import argparse
import os
import time
import threading

# arguments
parser = argparse.ArgumentParser(
    description="Add some description",
    formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("-V", "--verbose", action="store_true",
    help="show verbose, will create a timer print iocbs")
parser.add_argument("-S", "--silence", action="store_true",
    help="do not print each iocb")

args = parser.parse_args()
silence = args.silence
verbose = args.verbose


bpf_source = """
#include <linux/aio.h>

struct tp_io_submit_args {
    u64 __unused__;
    int __syscall_nr;
    aio_context_t ctx_id;
    long nr;
    struct iocb * * iocbpp;
};

struct tp_io_submit_args_ret {
    u64 __unused__;
    int __syscall_nr;
    long ret;
};

struct tp_io_getevents_args {
    u64 __unused__;
    int __syscall_nr;
    aio_context_t ctx_id;
    long min_nr;
    long nr;
    struct io_event * events;
    struct __kernel_timespec * timeout;
};
struct tp_io_getevents_args_ret {
    u64 __unused__;
    int __syscall_nr;
    long ret;
};

#define IO_SUBMIT   1
#define IO_GETEVENTS    2

struct event {
    char comm[TASK_COMM_LEN];
    u32 pid;
    /* IO_SUBMIT, IO_GETEVENTS */
    int io_type;
    /* index in nr */
    int idx;
    /* struct iocb address */
    u64 iocb;
};

BPF_PERF_OUTPUT(events);

typedef struct data_key {
    u32 pid;
} data_key_t;

typedef struct data_val_io_submit {
    struct iocb **iocbpp;
} data_val_io_submit_t;

typedef struct data_val_io_getevents {
    struct io_event *events;
} data_val_io_getevents_t;

BPF_HASH(hash_io_submit, data_key_t, data_val_io_submit_t);
BPF_HASH(hash_io_getevents, data_key_t, data_val_io_getevents_t);

static int __trace(void *ctx, int io_type, int idx, u64 iocb)
{
    struct event event = {};
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    bpf_get_current_comm(&event.comm, sizeof(event.comm));
    event.pid = pid;
    event.io_type = io_type;
    event.iocb = iocb;
    event.idx = idx;
    events.perf_submit(ctx, &event, sizeof(event));
    return 0;
}

#define TRY_NR  1024

int trace_io_submit_enter(struct tp_io_submit_args *args)
{
    data_key_t key = {0};
    data_val_io_submit_t val = {0};
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    key.pid = pid;
    val.iocbpp = args->iocbpp;
    hash_io_submit.update(&key, &val);
    return 0;
}

int trace_io_submit_exit(struct tp_io_submit_args_ret *args)
{
    int i, ret = 0;
    data_key_t key = {0};
    data_val_io_submit_t *valp;
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    key.pid = pid;
    valp = hash_io_submit.lookup(&key);
    if (valp == 0)
        return 0;
    hash_io_submit.delete(&key);

    struct iocb **iocbpp = valp->iocbpp;
    long nr = args->ret;

    for (i = 0; i < TRY_NR; i++) {
        if (i >= nr)
            break;
        u64 addr;
        bpf_probe_read(&addr, sizeof(u64), &iocbpp[i]);
        ret |= __trace(args, IO_SUBMIT, i, addr);
    }
    return ret;
}

int trace_io_getevents_enter(struct tp_io_getevents_args *args)
{
    data_key_t key = {0};
    data_val_io_getevents_t val = {0};
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    key.pid = pid;
    val.events = args->events;
    hash_io_getevents.update(&key, &val);
    return 0;
}

int trace_io_getevents_exit(struct tp_io_getevents_args_ret *args)
{
    int i, ret = 0;
    data_key_t key = {0};
    data_val_io_getevents_t *valp;
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    key.pid = pid;
    valp = hash_io_getevents.lookup(&key);
    if (valp == 0)
        return 0;
    hash_io_getevents.delete(&key);

    struct io_event *events = valp->events;
    long nr = args->ret;

    for (i = 0; i < TRY_NR; i++) {
        if (i >= nr)
            break;
        struct io_event *event = &events[i];
        u64 addr;
        bpf_probe_read(&addr, sizeof(u64), &event->obj);
        ret |= __trace(args, IO_GETEVENTS, i, addr);
    }
    return ret;
}
"""

# Record all iocb that still in kernel, which is already io_submit, but
# never io_getevents.
hash_iocbs = {}

stop_timer = False
io_type_str = {}
io_type_str[1] = b"SUBMIT"
io_type_str[2] = b"GETEVT"

bpf = BPF(text = bpf_source)
bpf.attach_tracepoint(tp = "syscalls:sys_enter_io_submit", fn_name = "trace_io_submit_enter")
bpf.attach_tracepoint(tp = "syscalls:sys_exit_io_submit", fn_name = "trace_io_submit_exit")
bpf.attach_tracepoint(tp = "syscalls:sys_enter_io_getevents", fn_name = "trace_io_getevents_enter")
bpf.attach_tracepoint(tp = "syscalls:sys_exit_io_getevents", fn_name = "trace_io_getevents_exit")
if BPF.tracepoint_exists("syscalls", "sys_enter_io_pgetevents"):
    bpf.attach_tracepoint(tp = "syscalls:sys_enter_io_pgetevents", fn_name = "trace_io_getevents_enter")
    bpf.attach_tracepoint(tp = "syscalls:sys_exit_io_pgetevents", fn_name = "trace_io_getevents_exit")


def record_iocbs(event):
    # Record iocbs
    if event.io_type == 1: # IO_SUBMIT
        hash_iocbs[event.iocb] = [event.pid, event.comm, event.iocb];
    elif event.io_type == 2: # IO_GETEVENTS
        hash_iocbs.pop(event.iocb)

def print_iocbs():
    print(hash_iocbs)

def print_event(cpu, data, size):
    event = bpf["events"].event(data)
    record_iocbs(event)
    if not silence:
        printb(b"%-8s %-8d %-16s %-8s %-8d %-16lx" % (
            strftime("%H:%M:%S").encode('ascii'),
            event.pid,
            event.comm,
            io_type_str[event.io_type],
            event.idx,
            event.iocb
        ));
    if verbose:
        print_iocbs()


print("Tracing aio latency ... Hit Ctrl-C to end")

if not silence:
    print("%-8s %-8s %-16s %-8s %-8s %-16s" %
            ("TIME", "PID", "COMM", "IOTYPE", "IDX", "IOCB"))

def iocbs_timer_callback():
    global stop_timer
    while True:
        time.sleep(2)
        print_iocbs()
        if stop_timer:
            break

# Start printer timer if verbose
if verbose:
    iocbs_print_timer = threading.Thread(target=iocbs_timer_callback)
    iocbs_print_timer.start()

bpf["events"].open_perf_buffer(print_event)
while True:
    try:
        bpf.perf_buffer_poll()
    except KeyboardInterrupt:
        stop_timer = True
        if verbose:
            iocbs_print_timer.join()
        exit()
