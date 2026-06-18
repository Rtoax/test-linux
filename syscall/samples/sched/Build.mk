# SPDX-License-Identifier: GPL-3.0
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

post-y := post0

str2cpuset-objs := ${SCHED_HELPERS}
getcpu-objs := ${SCHED_HELPERS}
sched_setattr-objs := ${SCHED_HELPERS}
sched_setscheduler-objs := ${SCHED_HELPERS}
sched_getscheduler-objs := ${SCHED_HELPERS}
sched_getaffinity-objs := ${TLC_HELPERS}
sched_getcpu-objs := ${SCHED_HELPERS}

CFLAGS := -D__USE_GNU
CFLAGS += -I../../../
CFLAGS += -pthread
