include bpf/bpftrace.mk

target-bt-y += arithmetic.bt
target-bt-y += begin.bt
target-bt-$(call bpftrace_gt,0,20,2) += begin-multi.bt
target-bt-y += c-preprocessor.bt
target-bt-y += config.bt
target-bt-$(call bpftrace_gt,0,21,0) += getopt.bt getopt.bt.1 getopt.bt.9 getopt.bt.10
target-bt-$(call bpftrace_gt,0,20,2) += import.bt
target-bt-y += parent.bt
target-bt-$(call bpftrace_gt,0,20,2) += pcomm.bt
target-bt-$(call bpftrace_ge,0,25,0) += signal_name.bt
target-bt-$(call bpftrace_gt,0,20,2) += strerror.bt
target-bt-y += struct.bt
target-bt-y += syscall_name.bt
target-bt-$(call bpftrace_gt,0,20,2) += return.bt
target-bt-y += ustack.bt
target-bt-y += unroll.bt
ifneq ($(wildcard ../../../compiler/dwarf/samples/hello.dw5),)
  target-bt-y += dw_ustack.bt
endif

ARGS_dw_ustack.bt := -c ../../../compiler/dwarf/samples/hello.dw5

ARGS_getopt.bt.1 := -- --num=1
ARGS_getopt.bt.9 := -- --num=9
ARGS_getopt.bt.10 := -- --num=10
