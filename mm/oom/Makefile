TARGETS := oom
TARGETS += popen
TARGETS += adaptive-oom-score

TARGETS_BPF := adaptive-oom-score.bpf.o
TARGETS_POST := adaptive-oom-score.skel.h

VMLINUX_H := vmlinux.h
TARGETS_PREP := ${VMLINUX_H}

CFLAGS_popen = -DPOPEN=1
LDFLAGS_adaptive-oom-score := -lbpf

include ../../template/main.mk

include ../../bpf/bpftool/vmlinux.h.mk

oom_helpers.o: oom_helpers.h
proc_helpers.o: proc_helpers.h

oom: oom.o oom_helpers.o proc_helpers.o
popen: popen.o oom_helpers.o proc_helpers.o

adaptive-oom-score.o: ${VMLINUX_H} adaptive-oom-score.skel.h
adaptive-oom-score: adaptive-oom-score.o oom_helpers.o proc_helpers.o
