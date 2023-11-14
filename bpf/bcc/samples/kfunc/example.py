#!/bin/env python3
from bcc import BPF

bpf_source = """
#include <uapi/linux/ptrace.h>

KRETFUNC_PROBE(EXEC, const char __user *filename,
               const char *const *argv, const char *const *envp, int ret)
{
    char comm[16];
    bpf_get_current_comm(&comm, sizeof(comm));
    bpf_trace_printk("executing program: %s\\n", comm);
    return 0;
}
"""

if not BPF.support_kfunc():
    print("Not support kfunc")
    exit()

bpf = BPF(text='')
execve = bpf.get_syscall_prefix().decode() + 'execve'
bpf_source = bpf_source.replace('EXEC', execve)
print("Attach %s" % execve)

bpf = BPF(text=bpf_source)
bpf.trace_print()
