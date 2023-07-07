
TARGETS := fallocate
TARGETS += faccessat2
TARGETS += getrlimit
TARGETS += nr
TARGETS += openat2
TARGETS += opendir
TARGETS += pause
TARGETS += pidfd_open
TARGETS += readlink
TARGETS += getcwd
TARGETS += getpid
TARGETS += setgid setegid
TARGETS += setuid seteuid
TARGETS += sched_getaffinity
TARGETS += inotify_init

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
# TODO: Remove openat2 from TARGETS
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: nr.h ${TARGETS}
	@echo
	make -C ioctl
	make -C epoll
	make -C socket
	make -C prctl
	@echo -e " \033[1;33m Done \033[m"

nr.h:
	$(shell sh nr.sh)

# Add more object.o file
fallocate: fallocate.o
faccessat2: faccessat2.o
getrlimit: getrlimit.o
nr: nr.o
openat2: openat2.o
opendir: opendir.o
pause: pause.o
pidfd_open: pidfd_open.o
readlink: readlink.o
getcwd: getcwd.o
getpid: getpid.o
setgid: setgid.o
setegid: setegid.o
setuid: setuid.o
seteuid: seteuid.o
sched_getaffinity: sched_getaffinity.o
inotify_init: inotify_init.o


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
	./fallocate.out

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	make -C ioctl clean
	make -C epoll clean
	make -C prctl clean
	make -C socket clean
	@rm -f ${TARGETS} *.o *.d *.txt nr.h
