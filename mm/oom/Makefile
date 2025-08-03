targets := oom
targets += popen
targets += adaptive-oom-score

targets-bpf := adaptive-oom-score.bpf.o
targets-post := adaptive-oom-score.skel.h

VMLINUX_H := vmlinux.h
targets-prep := ${VMLINUX_H}

CFLAGS_popen = -DPOPEN=1
LDFLAGS_adaptive-oom-score := -lbpf

include ../../template/main.mk

oom_helpers.o: oom_helpers.h
proc_helpers.o: proc_helpers.h

oom: oom.o oom_helpers.o proc_helpers.o
popen: popen.o oom_helpers.o proc_helpers.o

adaptive-oom-score.bpf.o: adaptive-oom-score.h
adaptive-oom-score.o: ${VMLINUX_H} adaptive-oom-score.skel.h adaptive-oom-score.h
adaptive-oom-score: adaptive-oom-score.o oom_helpers.o proc_helpers.o
