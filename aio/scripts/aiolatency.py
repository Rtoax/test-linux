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

bpf_source = """
#include <linux/aio.h>

struct tp_io_submit_args {
    u64 __unused__;
    int __syscall_nr;
    aio_context_t ctx_id;
    long nr;
    struct iocb * * iocbpp;
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

#define TRY_NR  128

int trace_io_submit(struct tp_io_submit_args *args)
{
    int i, ret = 0;
    struct iocb **iocbpp = args->iocbpp;

    for (i = 0; i < 4; i++) {
        if (i >= args->nr)
            break;
        u64 addr;
        bpf_probe_read(&addr, sizeof(u64), &iocbpp[i]);
        ret |= __trace(args, IO_SUBMIT, i, addr);
    }
    return ret;
}

int trace_io_getevents(struct tp_io_getevents_args *args)
{
    int i, ret = 0;
    struct io_event *events = args->events;

    for (i = 0; i < TRY_NR; i++) {
        if (i >= args->nr)
            break;
        struct io_event *event = &events[i];
        u64 addr;
        bpf_probe_read(&addr, sizeof(u64), &event->obj);
        ret |= __trace(args, IO_GETEVENTS, i, addr);
    }
    return ret;
}
"""

bpf = BPF(text = bpf_source)
bpf.attach_tracepoint(tp = "syscalls:sys_enter_io_submit", fn_name = "trace_io_submit")
bpf.attach_tracepoint(tp = "syscalls:sys_enter_io_getevents", fn_name = "trace_io_getevents")

def print_event(cpu, data, size):
    event = bpf["events"].event(data)
    printb(b"%-8s %-8d %-16s %-8d %-8d %-16lx" % (
        strftime("%H:%M:%S").encode('ascii'),
        event.pid,
        event.comm,
        event.io_type,
        event.idx,
        event.iocb
    ));

print("Tracing aio latency ... Hit Ctrl-C to end")
print("%-8s %-8s %-16s %-8s %-8s %-16s" %
      ("TIME", "PID", "COMM", "IOTYPE", "IDX", "IOCB"))

bpf["events"].open_perf_buffer(print_event)
while True:
    try:
        bpf.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
