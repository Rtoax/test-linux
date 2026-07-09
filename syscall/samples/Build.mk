# SPDX-License-Identifier: GPL-3.0
include cross-compile.mk

subdir-y += access
subdir-y += aio
subdir-y += bpf
subdir-y += capability
subdir-y += io
subdir-y += ioctl
subdir-y += poll
subdir-y += dup
subdir-y += cache
subdir-y += chroot
subdir-y += epoll
subdir-y += msgqueue
subdir-y += resource
subdir-y += ptrace
subdir-y += fcntl
subdir-y += pipe
subdir-y += mm
subdir-y += time
subdir-y += timerfd
subdir-y += times
subdir-y += flock
subdir-y += vfs
subdir-y += fanotify
subdir-y += inotify
subdir-y += sched
subdir-y += seccomp
subdir-y += semaphore
subdir-y += signal
subdir-y += shm
subdir-y += socket
subdir-y += utime
subdir-y += prctl
subdir-y += perf_event_open
subdir-${IS_X86_64} += arch_prctl
subdir-y += pidfd
subdir-y += reboot
subdir-y += wait
subdir-y += uio
subdir-y += read
subdir-y += sendfile
subdir-y += sysinfo
subdir-y += mount
subdir-y += module
subdir-y += random
subdir-${IS_X86_64} += ldt
subdir-y += xattr
subdir-y += truncate
subdir-y += write
subdir-y += lseek

target-y += acct
target-y += chdir fchdir
target-y += chown fchown fchownat
target-y += fdopen
target-y += kcmp
target-y += nr
target-y += opendir
target-y += pause
target-y += personality
target-y += readlink
target-y += rename
target-y += getcwd
target-y += gettid
target-y += getpid getpgid
target-y += setpgid setpgid-fork
target-y += setgid setegid setregid
target-y += getuid setuid seteuid setreuid
target-y += setpgrp
target-y += tee tee2
target-y += close
ifneq ($(wildcard /usr/include/linux/close_range.h),)
  target-y += close_range
else
  $(warning "WARNING: not found /usr/include/linux/close_range.h")
endif
target-y += setitimer
target-y += unlink
target-y += rmdir
target-y += uname
target-y += userfaultfd
target-y += symlink
target-y += readdir
target-y += getdents
target-y += getgroups
target-y += gethostname sethostname
target-y += gethostid sethostid
target-y += vhangup
target-y += syscall
target-y += sync syncfs
target-y += getsid setsid
target-y += getdomainname
target-y += link
target-y += fsync fdatasync
target-y += sync_file_range
target-y += getpagesize
target-y += ioprio_get ioprio_set

ifndef NOCPP
  target-cpp-y += readlink2
endif

ifeq ($(shell uname -m),x86_64)
  target-y += sysctl
endif
ifeq ($(shell uname -m),aarch64)
# TODO: Remove openat2 from targets
  target-y := $(filter-out pause, $(target-y))
endif
ifeq ($(shell uname -m),sw_64)
  target-y := $(filter-out pause, $(target-y))
endif
ifeq ($(shell uname -m),riscv64)
  target-y := $(filter-out pause, $(target-y))
  target-y := $(filter-out chmod, $(target-y))
  target-y := $(filter-out getdents, $(target-y))
endif

CFLAGS += -I../../
LDFLAGS += -pthread

CXXFLAGS_readlink2 := -std=c++17 -lstdc++

prep-y := nr.h
target-clean-y := clean0
