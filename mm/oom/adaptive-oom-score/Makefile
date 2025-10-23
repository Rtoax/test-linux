__USE_PROC_HELPERS__ = y
__USE_OOM_HELPERS__ = y

target-y := adaptive-oom-score

target-bpf-y := memory.bpf.o
target-post-y := memory.skel.h

VMLINUX_H := vmlinux.h
target-prep-y := ${VMLINUX_H}

LDFLAGS_adaptive-oom-score := -lbpf

include ../../../cgroup/libcgroup/libcgroup.mk
include ../../../template/main.mk

memory.bpf.o: memory.h
adaptive-oom-score.o: ${VMLINUX_H} memory.skel.h memory.h
adaptive-oom-score: adaptive-oom-score.o ${OOM_HELPERS} ${PROC_HELPERS}
