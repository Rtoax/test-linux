include libcgroup.mk
include helpers.mk

subdir-y := adaptive-oom-score

target-y := oom
target-y += oom_minimal

target-libso-y := liboom_helpers.so
target-liba-y := liboom_helpers.a

liboom_helpers.a-objs := ${OUTPUT}oom_helpers.a.o
liboom_helpers.so-objs := ${OUTPUT}oom_helpers.so.o
oom-objs := ${OOM_HELPERS} ${PROC_HELPERS} ${C_HELPERS}

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}
LDFLAGS += -Wl,-rpath,$(shell pwd)
