# SPDX-License-Identifier: GPL-3.0
sub-dir :=
sub-dir += clone
sub-dir += fork
sub-dir += namespace

targets :=
targets += cpuset CPU_SETSIZE CPU_ALLOC str2cpuset
targets += getcpu sched_getcpu
targets += nice nice-latency
targets += sched_setattr
targets += sched_setscheduler sched_getscheduler policy
targets += sched_getparam sched_setparam
targets += sched_getaffinity
targets += sched_get_priority_max sched_get_priority_min
targets += sched_rr_get_interval
targets += sched_yield
targets += taskset
targets += daemon

CFLAGS := -D__USE_GNU
CFLAGS += -I../../../
CFLAGS += -pthread

targets-test := test0

include ../../../template/main.mk

sched_helpers.o: sched_helpers.h

cpuset: cpuset.o
CPU_SETSIZE: CPU_SETSIZE.o
CPU_ALLOC: CPU_ALLOC.o
str2cpuset: str2cpuset.o sched_helpers.o
nice: nice.o
nice-latency: nice-latency.o
getcpu: getcpu.o sched_helpers.o
sched_setattr: sched_setattr.o sched_helpers.o
sched_getparam: sched_getparam.o
sched_setparam: sched_setparam.o
sched_setscheduler: sched_setscheduler.o sched_helpers.o
sched_getscheduler: sched_getscheduler.o sched_helpers.o
policy: policy.o
sched_get_priority_max: sched_get_priority_max.o
sched_get_priority_min: sched_get_priority_min.o
sched_getaffinity: sched_getaffinity.o
sched_rr_get_interval: sched_rr_get_interval.o
sched_getcpu: sched_getcpu.o sched_helpers.o
sched_yield: sched_yield.o
setns: setns.o
taskset: taskset.o
daemon: daemon.o

test0:
	$(call log_tgt_exe,TEST,,$(@))
	$(Q)sudo chrt -r 10 ./sched_rr_get_interval
	$(Q)sudo chrt -f 10 ./sched_rr_get_interval

