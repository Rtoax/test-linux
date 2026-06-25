include bpf/bpftrace.mk

subdir-y += playground

bpftrace-y += base.bt
bpftrace-y += let.bt
bpftrace-y += strcap.bt
bpftrace-y += strlen.bt
