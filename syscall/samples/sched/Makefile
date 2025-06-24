# SPDX-License-Identifier: GPL-3.0
sub-dir :=
sub-dir += clone
sub-dir += fork
sub-dir += namespace

TARGETS :=
TARGETS += cpuset CPU_SETSIZE CPU_ALLOC str2cpuset
TARGETS += getcpu sched_getcpu
TARGETS += nice nice-latency
TARGETS += sched_setattr
TARGETS += sched_setscheduler sched_getscheduler policy
TARGETS += sched_getparam sched_setparam
TARGETS += sched_getaffinity
TARGETS += sched_get_priority_max sched_get_priority_min
TARGETS += sched_rr_get_interval
TARGETS += sched_yield
TARGETS += taskset
TARGETS += daemon

CFLAGS := -D__USE_GNU
CFLAGS += -I../../../
CFLAGS += -pthread

TARGETS_TEST := test0

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
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	sudo chrt -r 10 ./sched_rr_get_interval
	sudo chrt -f 10 ./sched_rr_get_interval

