include bpf/bpftrace.mk

bpftrace-y += base.bt
bpftrace-$(call bpftrace_gt,0,13,1) += complex.bt
