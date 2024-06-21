sub-dir :=
sub-dir += clone

TARGETS += cpuset CPU_SETSIZE CPU_ALLOC str2cpuset
TARGETS += getcpu sched_getcpu
TARGETS += nice
TARGETS += sched_setattr
TARGETS += sched_setscheduler sched_getscheduler
TARGETS += sched_getparam sched_setparam
TARGETS += sched_getaffinity
TARGETS += sched_get_priority_max sched_get_priority_min
TARGETS += sched_rr_get_interval
TARGETS += sched_yield
TARGETS += fork vfork fork-share
TARGETS += setns
TARGETS += unshare
TARGETS += taskset

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	make -C clone
	@echo -e " \033[1;33m Done \033[m"

cpuset: cpuset.o
CPU_SETSIZE: CPU_SETSIZE.o
CPU_ALLOC: CPU_ALLOC.o
str2cpuset: str2cpuset.o helpers.o
nice: nice.o
getcpu: getcpu.o helpers.o
sched_setattr: sched_setattr.o helpers.o
sched_getparam: sched_getparam.o
sched_setparam: sched_setparam.o
sched_setscheduler: sched_setscheduler.o helpers.o
sched_getscheduler: sched_getscheduler.o helpers.o
sched_get_priority_max: sched_get_priority_max.o
sched_get_priority_min: sched_get_priority_min.o
sched_getaffinity: sched_getaffinity.o
sched_rr_get_interval: sched_rr_get_interval.o
sched_getcpu: sched_getcpu.o helpers.o
sched_yield: sched_yield.o
fork: fork.o
vfork: vfork.o
fork-share: fork-share.o
setns: setns.o
unshare: unshare.o
taskset: taskset.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	sudo chrt -r 10 ./sched_rr_get_interval
	sudo chrt -f 10 ./sched_rr_get_interval

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	make -C clone clean
	@rm -f ${TARGETS} \
		*.o *.d

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)

$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean

