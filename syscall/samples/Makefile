# SPDX-License-Identifier: GPL-3.0
include ../../compiler/cross-compile.mk

sub-dir :=
sub-dir += access
sub-dir += aio
sub-dir += bpf
sub-dir += capability
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

include ../../template/subdir-header.mk

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
TARGETS += close
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
TARGETS += read
TARGETS += getdents
TARGETS += getgroups
TARGETS += gethostname sethostname
TARGETS += gethostid sethostid
TARGETS += vhangup
TARGETS += syscall
TARGETS += sync syncfs
TARGETS += getsid setsid
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

CFLAGS += -I../../
CFLAGS += -pthread

CFLAGS_write := -Wno-error=unused-variable
CXXFLAGS_readlink2 := -std=c++17 -lstdc++

TARGETS_PREP := nr.h
TARGETS_CLEAN := clean0

include ../../template/main.mk

nr.h: nr.sh
	$(shell bash nr.sh)

syscall_helpers.o: syscall_helpers.h

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
nr.o: nr2s.h nr.h
opendir: opendir.o
pause: pause.o
personality: personality.o
lseek: lseek.o
rename: rename.o
readlink: readlink.o
readlink2: readlink2.cpp.o
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
close: close.o
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
read: read.o
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
link: link.o syscall_helpers.o
fsync: fsync.o
fdatasync: fdatasync.o
sync_file_range: sync_file_range.o
getpagesize: getpagesize.o
ioprio_get: ioprio_get.o
ioprio_set: ioprio_set.o

clean0:
	${Q}rm -rf nr.h *.txt testfile
