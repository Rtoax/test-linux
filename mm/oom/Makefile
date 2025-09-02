targets := oom
targets += oom_minimal
targets += adaptive-oom-score

targets-bpf := adaptive-oom-score.bpf.o
targets-post := adaptive-oom-score.skel.h

VMLINUX_H := vmlinux.h
targets-prep := ${VMLINUX_H}

LDFLAGS_adaptive-oom-score := -lbpf

include ../../cgroup/libcgroup/libcgroup.mk
include ../../template/main.mk

oom_helpers.o: oom_helpers.h
proc_helpers.o: proc_helpers.h

oom: oom.o oom_helpers.o proc_helpers.o
oom_minimal: oom_minimal.o

adaptive-oom-score.bpf.o: adaptive-oom-score.h
adaptive-oom-score.o: ${VMLINUX_H} adaptive-oom-score.skel.h adaptive-oom-score.h
adaptive-oom-score: adaptive-oom-score.o oom_helpers.o proc_helpers.o
