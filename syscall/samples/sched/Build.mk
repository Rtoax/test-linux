# SPDX-License-Identifier: GPL-3.0
__USE_C_HELPERS__ = y

include helpers.mk

subdir-y += clone
subdir-y += fork
subdir-y += namespace

target-y += cpuset CPU_SETSIZE CPU_ALLOC str2cpuset
target-y += getcpu sched_getcpu
target-y += nice nice-latency
target-y += sched_setattr
target-y += sched_setscheduler sched_getscheduler policy
target-y += sched_getparam sched_setparam
target-y += sched_getaffinity
target-y += sched_get_priority_max sched_get_priority_min
target-y += sched_rr_get_interval
target-y += sched_yield
target-y += taskset
target-y += daemon

target-libso-y := libsched_helpers.so
target-liba-y := libsched_helpers.a

target-post-y := post0

libsched_helpers.a-objs := sched_helpers.a.o
libsched_helpers.so-objs := sched_helpers.so.o

str2cpuset-objs := libsched_helpers.a
getcpu-objs := libsched_helpers.a
sched_setattr-objs := libsched_helpers.a
sched_setscheduler-objs := libsched_helpers.a
sched_getscheduler-objs := libsched_helpers.a
sched_getaffinity-objs := ${C_HELPERS}
sched_getcpu-objs := libsched_helpers.a

CFLAGS := -D__USE_GNU
CFLAGS += -I../../../
CFLAGS += -pthread
