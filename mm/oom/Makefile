__USE_PROC_HELPERS__ = y

subdir-y := adaptive-oom-score

target-y := oom
target-y += oom_minimal

target-libso-y := liboom_helpers.so

VMLINUX_H := vmlinux.h
target-prep-y := ${VMLINUX_H}

LDFLAGS += -Wl,-rpath,$(shell pwd)

include ../../cgroup/libcgroup/libcgroup.mk
include ../../template/main.mk

oom_helpers.so.o: oom_helpers.h
liboom_helpers.so: oom_helpers.so.o

oom: oom.o liboom_helpers.so ${PROC_HELPERS}
oom_minimal: oom_minimal.o
