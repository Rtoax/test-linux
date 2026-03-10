__USE_C_HELPERS__ = y
__USE_PROC_HELPERS__ = y
__USE_OOM_HELPERS__ = y

include libcgroup.mk
include helpers.mk

target-y := adaptive-oom-score

target-bpf-y := memory.bpf.o
target-post-y := memory.skel.h

adaptive-oom-score-objs := ${OOM_HELPERS} ${PROC_HELPERS} ${C_HELPERS}

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}
LDFLAGS_adaptive-oom-score := -lbpf

include main.mk

memory.bpf.o: memory.h
adaptive-oom-score.o: memory.skel.h memory.h
