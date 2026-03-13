include libcgroup.mk
include helpers.mk

target-y := adaptive-oom-score

target-bpf-y := ${OUTPUT}memory.bpf.o
target-post-y := ${OUTPUT}memory.skel.h

adaptive-oom-score-objs := ${OOM_HELPERS} ${PROC_HELPERS} ${C_HELPERS}

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}
LDFLAGS_adaptive-oom-score := -lbpf
