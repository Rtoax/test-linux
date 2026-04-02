include libcgroup.mk
include helpers.mk

subdir-y := adaptive-oom-score

target-y := oom
target-y += oom_minimal

oom-objs := ${OOM_HELPERS} ${PROC_HELPERS} ${TLC_HELPERS}

CFLAGS += ${libcgroup-cflags}
LDFLAGS += ${libcgroup-ldflags}
LDFLAGS += -Wl,-rpath,$(shell pwd)
