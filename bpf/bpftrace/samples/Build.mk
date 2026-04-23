include bpf/bpftrace.mk

target-bt-y := arithmetic.bt
target-bt-$(call bpftrace_gt,0,21,0) += getopt.bt getopt.bt.1 getopt.bt.9 getopt.bt.10
target-bt-y += parent.bt
target-bt-y += stack-limit-is-exceeded.bt
target-bt-y += return.bt
target-bt-y += unroll.bt

ARGS_getopt.bt.1 := -- --num=1
ARGS_getopt.bt.9 := -- --num=9
ARGS_getopt.bt.10 := -- --num=10
