#!/usr/bin/env python
#
# Tracing KVM set memory region
#
# Copyright (C) 2022-2026 Rong Tao
#
# 2022-10-20    Rong Tao    Create this

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.containers import filter_by_containers
from bcc.utils import printb
import argparse
import os

bpf_text = """
#include <linux/sched.h>
#include <uapi/linux/kvm.h>

struct mem_region {
    int pid;
    char comm[TASK_COMM_LEN];
    unsigned int slot;
    unsigned long gpa;
    unsigned long size;
    unsigned long hva;
};

BPF_PERF_OUTPUT(mem_region_events);

int trace_region(struct pt_regs *ctx)
{
    int ret = PT_REGS_RC(ctx);

    struct mem_region data = {};
    struct kvm_userspace_memory_region *region =
        (struct kvm_userspace_memory_region *)PT_REGS_PARM2(ctx);

    data.pid = bpf_get_current_pid_tgid() >> 32;
    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.slot = region->slot;
    data.gpa = region->guest_phys_addr;
    data.size = region->memory_size;
    data.hva = region->userspace_addr;

    mem_region_events.perf_submit(ctx, &data, sizeof(data));

    return 0;
}
"""

def print_region(cpu, data, size):
    event = b["mem_region_events"].event(data)
    printb(b"%-16s %-8d %-8d %-016lx %-016lx %-8ld" %
        (event.comm, event.pid, event.slot, event.gpa, event.hva, event.size))

b = BPF(text=bpf_text)
b.attach_kprobe(event="__kvm_set_memory_region", fn_name="trace_region")

print("Tracing __kvm_set_memory_region ... Hit Ctrl-C to end")
print("%-16s %-8s %-8s %-16s %-16s %-8s" %
    ("COMM", "PID", "SLOT", "GPA", "HVA", "SIZE"))
b["mem_region_events"].open_perf_buffer(print_region)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
