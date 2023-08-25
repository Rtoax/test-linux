
TARGETS := fallocate
TARGETS += access faccessat2
TARGETS += fdopen
TARGETS += fork vfork
TARGETS += getrlimit setrlimit ulimit
TARGETS += nr
TARGETS += open openat2
TARGETS += opendir
TARGETS += pause
TARGETS += pidfd_open
TARGETS += readlink
TARGETS += getcwd
TARGETS += getpid
TARGETS += pipe
TARGETS += setgid setegid
TARGETS += setuid seteuid
TARGETS += sched_getaffinity
TARGETS += tee tee2
TARGETS += clone
TARGETS += setitimer
TARGETS += flock flock-2 flock-3 flock-4-thread
TARGETS += unlink
TARGETS += uname
TARGETS += userfaultfd
TARGETS += memfd_create memfd_create-dup2
TARGETS += membarrier
TARGETS += symlink
TARGETS += mlock mlockall

TARGETS_CPP += readlink2

ifeq ($(shell uname -m),x86_64)
TARGETS += get_thread_area
endif
ifeq ($(shell uname -m),aarch64)
# TODO: Remove openat2 from TARGETS
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: nr.h ${TARGETS} ${TARGETS_CPP}
	@echo
	make -C aio
	make -C ioctl
	make -C epoll
	make -C fanotify
	make -C inotify
	make -C signal
	make -C socket
	make -C prctl
	make -C arch_prctl
	@echo -e " \033[1;33m Done \033[m"

nr.h:
	$(shell sh nr.sh)

# Add more object.o file
fallocate: fallocate.o
faccessat2: faccessat2.o
access: access.o
fdopen: fdopen.o
fork: fork.o
vfork: vfork.o
get_thread_area: get_thread_area.o
getrlimit: getrlimit.o
setrlimit: setrlimit.o
ulimit: ulimit.o
nr: nr.o
open: open.o
openat2: openat2.o
opendir: opendir.o
pause: pause.o
pidfd_open: pidfd_open.o
pipe: pipe.o
readlink: readlink.o
readlink2: readlink2.opp
getcwd: getcwd.o
getpid: getpid.o
setgid: setgid.o
setegid: setegid.o
setuid: setuid.o
seteuid: seteuid.o
sched_getaffinity: sched_getaffinity.o
tee: tee.o
tee2: tee2.o
clone: clone.o
setitimer: setitimer.o
flock: flock.o
flock-2: flock-2.o
flock-3: flock-3.o
flock-4-thread: flock-4-thread.o
unlink: unlink.o
uname: uname.o
userfaultfd: userfaultfd.o
memfd_create: memfd_create.o
memfd_create-dup2: memfd_create-dup2.o
membarrier: membarrier.o
symlink: symlink.o
mlock: mlock.o
mlockall: mlockall.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.dpp: %.cpp
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CXX) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.opp: %.cpp %.dpp
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CXX) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

$(TARGETS_CPP): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CXX) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	make -C aio clean
	make -C ioctl clean
	make -C epoll clean
	make -C fanotify clean
	make -C inotify clean
	make -C signal clean
	make -C prctl clean
	make -C arch_prctl clean
	make -C socket clean
	@rm -f ${TARGETS} ${TARGETS_CPP} \
		*.o *.d *.opp *.dpp nr.h *.out \
		*.txt testfile

