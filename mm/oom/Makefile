TARGETS := oom
TARGETS += popen
TARGETS += adaptive-oom-score

TARGETS_BPF := adaptive-oom-score.bpf.o
TARGETS_POST := adaptive-oom-score.skel.h

CFLAGS_popen = -DPOPEN=1
LDFLAGS_adaptive-oom-score := -lbpf

include ../../template/main.mk

include ../../bpf/bpftool/vmlinux.h.mk

oom.o: oom_helpers.h
popen.o: oom_helpers.h
oom_helpers.o: oom_helpers.h

oom: oom.o oom_helpers.o
popen: popen.o oom_helpers.o

adaptive-oom-score.o: vmlinux.h adaptive-oom-score.skel.h
adaptive-oom-score: adaptive-oom-score.o
