
TARGETS := fallocate
TARGETS += access faccessat2
TARGETS += acct
TARGETS += chdir fchdir
TARGETS += chmod
TARGETS += chown fchown
TARGETS += fdopen
TARGETS += kcmp
TARGETS += execve execve-fork
TARGETS += nr
TARGETS += open openat2
TARGETS += opendir
TARGETS += pause
TARGETS += pidfd_open
TARGETS += readlink
TARGETS += getcwd
TARGETS += getpid
TARGETS += setgid setegid
TARGETS += setuid seteuid
TARGETS += tee tee2
TARGETS += clone
TARGETS += setitimer
TARGETS += unlink
TARGETS += uname
TARGETS += userfaultfd
TARGETS += symlink
TARGETS += lstat
TARGETS += readdir
TARGETS += write
TARGETS += getdents

TARGETS_CPP += readlink2

ifeq ($(shell uname -m),x86_64)
TARGETS += get_thread_area
TARGETS += sysctl
endif
ifeq ($(shell uname -m),aarch64)
# TODO: Remove openat2 from TARGETS
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: nr.h ${TARGETS} ${TARGETS_CPP}
	@echo
	make -C aio
	make -C ioctl
	make -C poll
	make -C epoll
	make -C resource
	make -C ptrace
	make -C fcntl
	make -C pipe
	make -C mm
	make -C time
	make -C flock
	make -C fanotify
	make -C inotify
	make -C signal
	make -C prctl
	make -C perf_event_open
	make -C arch_prctl
	@echo -e " \033[1;33m Done \033[m"

nr.h: nr.sh
	$(shell sh nr.sh)

# Add more object.o file
fallocate: fallocate.o
faccessat2: faccessat2.o
acct: acct.o
access: access.o
chmod: chmod.o
chown: chown.o
fchown: fchown.o
chdir: chdir.o
fchdir: fchdir.o
kcmp: kcmp.o
fdopen: fdopen.o
execve: execve.o
execve-fork: execve-fork.o
get_thread_area: get_thread_area.o
nr: nr.o
open: open.o
openat2: openat2.o
opendir: opendir.o
pause: pause.o
pidfd_open: pidfd_open.o
readlink: readlink.o
readlink2: readlink2.opp
getcwd: getcwd.o
getpid: getpid.o
setgid: setgid.o
setegid: setegid.o
setuid: setuid.o
seteuid: seteuid.o
tee: tee.o
tee2: tee2.o
clone: clone.o
setitimer: setitimer.o
unlink: unlink.o
uname: uname.o
userfaultfd: userfaultfd.o
sysctl: sysctl.o
symlink: symlink.o
lstat: lstat.o
readdir: readdir.o
write: write.o
getdents: getdents.o

CFLAGS_write := -Wno-error=unused-variable

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.opp: %.cpp
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -o $(@) -c $(<)

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
	make -C poll clean
	make -C epoll clean
	make -C resource clean
	make -C ptrace clean
	make -C fcntl clean
	make -C pipe clean
	make -C mm clean
	make -C time clean
	make -C flock clean
	make -C fanotify clean
	make -C inotify clean
	make -C signal clean
	make -C perf_event_open clean
	make -C prctl clean
	make -C arch_prctl clean
	@rm -rf ${TARGETS} ${TARGETS_CPP} \
		*.o *.opp nr.h *.out \
		*.txt testfile

