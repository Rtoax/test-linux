include bpf/bpftrace.mk

subdir-y += attribute

bpftrace-y += base.bt
bpftrace-y += enum.bt
bpftrace-y += offsetof.bt
bpftrace-y += union.bt
