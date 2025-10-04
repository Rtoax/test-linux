targets := adaptive-oom-score

targets-bpf := memory.bpf.o
targets-post := memory.skel.h

VMLINUX_H := vmlinux.h
targets-prep := ${VMLINUX_H}

LDFLAGS_adaptive-oom-score := -lbpf

include ../../../cgroup/libcgroup/libcgroup.mk
include ../../../template/main.mk

oom_helpers.o: oom_helpers.h
proc_helpers.o: proc_helpers.h

memory.bpf.o: memory.h
adaptive-oom-score.o: ${VMLINUX_H} memory.skel.h memory.h
adaptive-oom-score: adaptive-oom-score.o oom_helpers.o proc_helpers.o
