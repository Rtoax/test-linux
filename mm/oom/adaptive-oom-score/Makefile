include libcgroup.mk

__USE_C_HELPERS__ = y
__USE_PROC_HELPERS__ = y
__USE_OOM_HELPERS__ = y

target-y := adaptive-oom-score

target-bpf-y := memory.bpf.o
target-post-y := memory.skel.h

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}
LDFLAGS_adaptive-oom-score := -lbpf

include main.mk

memory.bpf.o: memory.h
adaptive-oom-score.o: memory.skel.h memory.h
adaptive-oom-score: adaptive-oom-score.o ${OOM_HELPERS} ${PROC_HELPERS} ${C_HELPERS}
