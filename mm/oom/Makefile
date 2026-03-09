include libcgroup.mk

__USE_C_HELPERS__ = y
__USE_PROC_HELPERS__ = y
__USE_OOM_HELPERS__ = y

subdir-y := adaptive-oom-score

target-y := oom
target-y += oom_minimal

target-libso-y := liboom_helpers.so
target-liba-y := liboom_helpers.a

liboom_helpers.a-objs := oom_helpers.a.o

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}
LDFLAGS += -Wl,-rpath,$(shell pwd)

include main.mk

oom_helpers.so.o: oom_helpers.h
liboom_helpers.so: oom_helpers.so.o

oom: oom.o ${OOM_HELPERS} ${PROC_HELPERS} ${C_HELPERS}
oom_minimal: oom_minimal.o
