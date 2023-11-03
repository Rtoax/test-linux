#!/bin/env python3
from bcc import BPF

bpf_source = """
#include <linux/sched.h>

struct tp_execve_args {
    u64 __unused__;
    int __syscall_nr;
    const char * filename;
    const char *const * argv;
    const char *const * envp;
};

struct tp_execveat_args {
    u64 __unused__;
    int __syscall_nr;
    int fd;
    const char * filename;
    const char *const * argv;
    const char *const * envp;
    int flags;
};

struct event {
    char comm[TASK_COMM_LEN];
    char filename[128];
};

BPF_PERF_OUTPUT(events);

static int trace_bpf_prog_load(void *ctx, const char *filename)
{
    struct event event = {};
    bpf_get_current_comm(&event.comm, sizeof(event.comm));
    bpf_probe_read_user(&event.filename, sizeof(event.filename), filename);
    events.perf_submit(ctx, &event, sizeof(event));
    return 0;
}

int trace_bpf_prog_load_execve(struct tp_execve_args *args)
{
    return trace_bpf_prog_load(args, args->filename);
}
int trace_bpf_prog_load_execveat(struct tp_execveat_args *args)
{
    return trace_bpf_prog_load(args, args->filename);
}
"""

print("Tracing execve ... Hit Ctrl-C to end")

bpf = BPF(text = bpf_source)
bpf.attach_tracepoint(tp = "syscalls:sys_enter_execve", fn_name = "trace_bpf_prog_load_execve")
if BPF.tracepoint_exists("syscalls", "sys_enter_execveat"):
    bpf.attach_tracepoint(tp = "syscalls:sys_enter_execveat", fn_name = "trace_bpf_prog_load_execveat")

def print_event(cpu, data, size):
    event = bpf["events"].event(data)
    print("%-16s %s" % (event.comm, event.filename));

bpf["events"].open_perf_buffer(print_event)
while True:
    try:
        bpf.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
