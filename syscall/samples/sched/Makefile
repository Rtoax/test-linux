# SPDX-License-Identifier: GPL-3.0
subdir-y :=
subdir-y += clone
subdir-y += fork
subdir-y += namespace

target-y :=
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

CFLAGS := -D__USE_GNU
CFLAGS += -I../../../
CFLAGS += -pthread

target-test-y := test0

include ../../../template/main.mk

sched_helpers.so.o: sched_helpers.h
libsched_helpers.so: sched_helpers.so.o

cpuset: cpuset.o
CPU_SETSIZE: CPU_SETSIZE.o
CPU_ALLOC: CPU_ALLOC.o
str2cpuset: str2cpuset.o libsched_helpers.so
nice: nice.o
nice-latency: nice-latency.o
getcpu: getcpu.o libsched_helpers.so
sched_setattr: sched_setattr.o libsched_helpers.so
sched_getparam: sched_getparam.o
sched_setparam: sched_setparam.o
sched_setscheduler: sched_setscheduler.o libsched_helpers.so
sched_getscheduler: sched_getscheduler.o libsched_helpers.so
policy: policy.o
sched_get_priority_max: sched_get_priority_max.o
sched_get_priority_min: sched_get_priority_min.o
sched_getaffinity: sched_getaffinity.o
sched_rr_get_interval: sched_rr_get_interval.o
sched_getcpu: sched_getcpu.o libsched_helpers.so
sched_yield: sched_yield.o
setns: setns.o
taskset: taskset.o
daemon: daemon.o

test0:
	$(call log_tgt_exe,TEST,,$(@))
	$(Q)sudo chrt -r 10 ./sched_rr_get_interval
	$(Q)sudo chrt -f 10 ./sched_rr_get_interval
