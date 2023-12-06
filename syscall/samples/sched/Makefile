
TARGETS += cpuset CPU_SETSIZE CPU_ALLOC str2cpuset
TARGETS += getcpu sched_getcpu
TARGETS += nice
TARGETS += sched_setscheduler sched_getscheduler
TARGETS += sched_getparam sched_setparam
TARGETS += sched_getaffinity
TARGETS += sched_get_priority_max sched_get_priority_min
TARGETS += sched_yield
TARGETS += fork vfork

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../../
CFLAGS += -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	make -C clone
	@echo -e " \033[1;33m Done \033[m"

cpuset: cpuset.o
CPU_SETSIZE: CPU_SETSIZE.o
CPU_ALLOC: CPU_ALLOC.o
str2cpuset: str2cpuset.o helpers.o
nice: nice.o
getcpu: getcpu.o helpers.o
sched_getparam: sched_getparam.o
sched_setparam: sched_setparam.o
sched_setscheduler: sched_setscheduler.o
sched_getscheduler: sched_getscheduler.o
sched_get_priority_max: sched_get_priority_max.o
sched_get_priority_min: sched_get_priority_min.o
sched_getaffinity: sched_getaffinity.o
sched_getcpu: sched_getcpu.o helpers.o
sched_yield: sched_yield.o
fork: fork.o
vfork: vfork.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	make -C clone clean
	@rm -f ${TARGETS} \
		*.o *.d

