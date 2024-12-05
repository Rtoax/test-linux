# SPDX-License-Identifier: GPL-3.0
SHELL = /bin/bash

sub-dir :=
sub-dir += access
ifneq ($(wildcard /usr/include/libaio.h),)
$(info Already install libaio development)
sub-dir += aio
endif
ifneq ($(wildcard /usr/include/sys/capability.h),)
$(info Already install capability development)
sub-dir += capability
endif
sub-dir += io
sub-dir += ioctl
sub-dir += poll
sub-dir += dup
sub-dir += cache
sub-dir += chroot
sub-dir += epoll
sub-dir += msgqueue
sub-dir += resource
sub-dir += ptrace
sub-dir += fcntl
sub-dir += pipe
sub-dir += mm
sub-dir += time
sub-dir += timerfd
sub-dir += times
sub-dir += flock
sub-dir += fs
sub-dir += vfs
sub-dir += fanotify
sub-dir += inotify
sub-dir += sched
sub-dir += seccomp
sub-dir += semaphore
sub-dir += signal
sub-dir += shm
sub-dir += socket
sub-dir += utime
sub-dir += prctl
sub-dir += perf_event_open
sub-dir += arch_prctl
sub-dir += pidfd
sub-dir += wait
sub-dir += uio
sub-dir += sendfile
sub-dir += sysinfo
sub-dir += mount
sub-dir += module
sub-dir += random
sub-dir += ldt
sub-dir += xattr
sub-dir += truncate

TARGETS :=
TARGETS += acct
TARGETS += chdir fchdir
TARGETS += chown fchown fchownat
TARGETS += fdopen
TARGETS += kcmp
TARGETS += execve execve-fork
TARGETS += nr
TARGETS += opendir
TARGETS += pause
TARGETS += personality
TARGETS += readlink
TARGETS += rename
TARGETS += getcwd
TARGETS += gettid
TARGETS += getpid getpgid
TARGETS += setpgid setpgid-fork
TARGETS += setgid setegid setregid
TARGETS += getuid setuid seteuid setreuid
TARGETS += setpgrp
TARGETS += tee tee2
ifneq ($(wildcard /usr/include/linux/close_range.h),)
TARGETS += close_range
else
$(warning "WARNING: not found /usr/include/linux/close_range.h")
endif
TARGETS += setitimer
TARGETS += unlink
TARGETS += rmdir
TARGETS += uname
TARGETS += userfaultfd
TARGETS += symlink
TARGETS += readdir
TARGETS += write
TARGETS += getdents
TARGETS += getgroups
TARGETS += gethostname sethostname
TARGETS += gethostid sethostid
TARGETS += vhangup
TARGETS += syscall
TARGETS += sync syncfs
TARGETS += getsid
TARGETS += setsid
TARGETS += getdomainname
TARGETS += lseek
TARGETS += link
TARGETS += fsync fdatasync
TARGETS += sync_file_range
TARGETS += getpagesize
TARGETS += ioprio_get ioprio_set

TARGETS_CPP :=
ifndef NOCPP
  TARGETS_CPP += readlink2
endif

ifeq ($(shell uname -m),x86_64)
TARGETS += sysctl
endif
ifeq ($(shell uname -m),aarch64)
# TODO: Remove openat2 from TARGETS
	TARGETS := $(filter-out pause, $(TARGETS))
endif
ifeq ($(shell uname -m),sw_64)
	TARGETS := $(filter-out pause, $(TARGETS))
endif
ifeq ($(shell uname -m),riscv64)
	TARGETS := $(filter-out pause, $(TARGETS))
	TARGETS := $(filter-out chmod, $(TARGETS))
	TARGETS := $(filter-out getdents, $(TARGETS))
endif

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

sub-dir-build := $(sub-dir:=.build)

.PHONY: build
build: nr.h ${TARGETS} ${TARGETS_CPP} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=) CC=$(CC) CXX=$(CXX)

nr.h: nr.sh
	$(shell bash nr.sh)

# Add more object.o file
acct: acct.o
chown: chown.o
fchown: fchown.o
fchownat: fchownat.o
chdir: chdir.o
fchdir: fchdir.o
kcmp: kcmp.o
fdopen: fdopen.o
execve: execve.o
execve-fork: execve-fork.o
nr: nr.o
opendir: opendir.o
pause: pause.o
personality: personality.o
lseek: lseek.o
rename: rename.o
readlink: readlink.o
readlink2: readlink2.opp
getcwd: getcwd.o
gettid: gettid.o
getpid: getpid.o
getpgid: getpgid.o
setgid: setgid.o
setegid: setegid.o
setregid: setregid.o
setpgid: setpgid.o
setpgid-fork: setpgid-fork.o
getuid: getuid.o
setuid: setuid.o
seteuid: seteuid.o
setreuid: setreuid.o
setpgrp: setpgrp.o
tee: tee.o
tee2: tee2.o
close_range: close_range.o
setitimer: setitimer.o
unlink: unlink.o
rmdir: rmdir.o
uname: uname.o
userfaultfd: userfaultfd.o
sysctl: sysctl.o
symlink: symlink.o
readdir: readdir.o
write: write.o
getdents: getdents.o
getgroups: getgroups.o
gethostname: gethostname.o
sethostname: sethostname.o
gethostid: gethostid.o
sethostid: sethostid.o
vhangup: vhangup.o
syscall: syscall.o
sync: sync.o
syncfs: syncfs.o
setsid: setsid.o
getsid: getsid.o
getdomainname: getdomainname.o
link: link.o helpers.o
fsync: fsync.o
fdatasync: fdatasync.o
sync_file_range: sync_file_range.o
getpagesize: getpagesize.o
ioprio_get: ioprio_get.o
ioprio_set: ioprio_set.o

CFLAGS_write := -Wno-error=unused-variable

PFX_CC := CC
ifeq ($(CC),clang)
  PFX_CC := CLANG
endif

%.o: %.c
	@echo -e "  ${PFX_CC}  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.opp: %.cpp
	@echo -e "  ${PFX_CC}  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CXX) $(CXXFLAGS) $(CXXFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

$(TARGETS_CPP): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CXX) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

sub-dir-clean := $(sub-dir:=.clean)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -rf ${TARGETS} ${TARGETS_CPP} \
		*.o *.opp nr.h *.out *.dat \
		*.txt testfile

$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
