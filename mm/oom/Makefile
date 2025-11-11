__USE_C_HELPERS__ = y
__USE_PROC_HELPERS__ = y
__USE_OOM_HELPERS__ = y

ifdef STATIC
  $(warning "WARNING: subdir adaptive-oom-score not support STATIC!!!")
else
  subdir-y := adaptive-oom-score
endif

target-y := oom
target-y += oom_minimal

target-libso-y := liboom_helpers.so
target-liba-y := liboom_helpers.a

VMLINUX_H := vmlinux.h
target-prep-y := ${VMLINUX_H}

LDFLAGS += -Wl,-rpath,$(shell pwd)

include ../../cgroup/libcgroup/libcgroup.mk
include ../../template/main.mk

oom_helpers.so.o: oom_helpers.h
liboom_helpers.so: oom_helpers.so.o
liboom_helpers.a: oom_helpers.a.o

oom: oom.o ${OOM_HELPERS} ${PROC_HELPERS} ${C_HELPERS}
oom_minimal: oom_minimal.o
