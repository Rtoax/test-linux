include bpf/bpftrace.mk

subdir-$(call bpftrace_gt,0,20,2) += import
subdir-y += macro
subdir-y += string
subdir-y += struct
subdir-y += test

bpftrace-y += arithmetic.bt
bpftrace-y += begin.bt
bpftrace-$(call bpftrace_gt,0,20,2) += begin-multi.bt
bpftrace-y += c-preprocessor.bt
bpftrace-y += config.bt
bpftrace-y += func.bt
bpftrace-$(call bpftrace_gt,0,21,0) += getopt.bt getopt.bt.1 getopt.bt.9 getopt.bt.10
bpftrace-y += parent.bt
bpftrace-$(call bpftrace_gt,0,20,2) += pcomm.bt
bpftrace-$(call bpftrace_ge,0,25,0) += signal_name.bt
bpftrace-$(call bpftrace_gt,0,20,2) += strerror.bt
bpftrace-y += syscall_name.bt
bpftrace-$(call bpftrace_gt,0,20,2) += return.bt
bpftrace-y += typeof.bt
bpftrace-y += ustack.bt
bpftrace-y += unroll.bt
ifneq ($(wildcard ../../../compiler/dwarf/samples/hello.dw5),)
  bpftrace-y += dw_ustack.bt
endif

BT_ARGS_dw_ustack.bt := -c ../../../compiler/dwarf/samples/hello.dw5

BT_ARGS_getopt.bt.1 := -- --num=1
BT_ARGS_getopt.bt.9 := -- --num=9
BT_ARGS_getopt.bt.10 := -- --num=10
