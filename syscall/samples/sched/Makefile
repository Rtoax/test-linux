# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

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

CC := gcc
CXX := g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

include ../../../template/subdir-header.mk

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

helpers.o: helpers.h

cpuset: cpuset.o
CPU_SETSIZE: CPU_SETSIZE.o
CPU_ALLOC: CPU_ALLOC.o
str2cpuset: str2cpuset.o helpers.o
nice: nice.o
nice-latency: nice-latency.o
getcpu: getcpu.o helpers.o
sched_setattr: sched_setattr.o helpers.o
sched_getparam: sched_getparam.o
sched_setparam: sched_setparam.o
sched_setscheduler: sched_setscheduler.o helpers.o
sched_getscheduler: sched_getscheduler.o helpers.o
policy: policy.o
sched_get_priority_max: sched_get_priority_max.o
sched_get_priority_min: sched_get_priority_min.o
sched_getaffinity: sched_getaffinity.o
sched_rr_get_interval: sched_rr_get_interval.o
sched_getcpu: sched_getcpu.o helpers.o
sched_yield: sched_yield.o
setns: setns.o
taskset: taskset.o
daemon: daemon.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	sudo chrt -r 10 ./sched_rr_get_interval
	sudo chrt -f 10 ./sched_rr_get_interval

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

include ../../../template/subdir-footer.mk

