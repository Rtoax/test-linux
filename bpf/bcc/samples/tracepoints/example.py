#!/bin/env python3
from bcc import BPF

bpf_source = """
int trace_bpf_prog_load(void *ctx) {
  char comm[16];
  bpf_get_current_comm(&comm, sizeof(comm));

  bpf_trace_printk("%s is loading a BPF program", comm);
  return 0;
}
"""

print("Tracing execve ... Hit Ctrl-C to end")

bpf = BPF(text = bpf_source)
bpf.attach_tracepoint(tp = "syscalls:sys_enter_execve", fn_name = "trace_bpf_prog_load")
bpf.trace_print()
