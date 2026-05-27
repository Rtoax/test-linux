include bpf/bpftrace.mk

subdir-y += attribute

bpftrace-y += base.bt
bpftrace-y += enum.bt
bpftrace-y += union.bt
