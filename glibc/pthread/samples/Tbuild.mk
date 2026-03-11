# SPDX-License-Identifier: GPL-3.0
__USE_C_HELPERS__ = y
__USE_PTHREAD_HELPERS__ = y
__USE_SCHED_HELPERS__ = y
OUTPUT := .output/

include arch.mk
include helpers.mk

target-y += foobar
target-y += atfork
target-y += create_thread
target-y += multi_thread_stress
target-y += dead_lock-1
target-y += dead_lock-2
target-y += attr_setstacksize
target-y += attr_setstack-1
target-y += attr_setstack-2
target-y += attr_setstack-3
target-y += attr_setdetachstate
target-y += attr_getstack
target-y += attr_getstacksize
target-y += attr_getdetachstate
target-y += attr_getinheritsched
target-y += attr_getschedpolicy
target-y += attr_init
target-y += barrier_init
target-y += cancel testcancel setcancelstate
target-y += create
target-y += create-deadline
target-y += cleanup_push
target-y += cleanup_push-deadlock
target-y += cleanup_push_defer_np
target-y += equal
target-y += exit
target-y += getschedparam
target-y += key_create setspecific getspecific
target-y += join-coredump
target-y += join tryjoin_np timedjoin_np detach
target-y += getname_np setname_np
target-y += rwlock_init rwlock_rdlock rwlockattr_setpshared
target-y += self
target-y += spin_lock
target-y += spin-latency spin-latency-loop
target-y += setaffinity_np
target-y += sigmask
target-y += kill
target-y += once
target-y += yield
target-y += mutexattr_setprioceiling
target-y += mutexattr_setprotocol
target-y += mutexattr_setpshared
target-y += mutexattr_setrobust
target-y += mutexattr_settype
target-y += mutex_consistent
target-y += mutex_getprioceiling
target-y += mutex_init
target-y += setconcurrency
target-y += cond_init
target-y += cond_wait
target-y += cond_broadcast cond_broadcast-1
target-y += cond_signal
target-y += condattr_init
target-y += condattr_getclock
target-y += condattr_setpshared
target-y += getcpuclockid
target-y += tls
target-y += taskset
target-y += rt_thread
target-y += cond-demo1 cond-demo2 cond-demo3-latency
target-${IS_X86_64} += mutex_latency
target-y += taskset_example

# glibc >= 2.34, pthread APIs move from libpthread.so to libc.so.
# ref: https://developers.redhat.com/articles/2021/12/17/why-glibc-234-removed-libpthread
LDFLAGS := -pthread
CFLAGS += -I$(shell realpath .)/../../../
ifeq ($(CC),clang)
  LDFLAGS += -Wl,-lm
else
  LDFLAGS += -lm
endif

CFLAGS_cond_broadcast := -DCOND_ATTR=1
CFLAGS_cond_signal := -DCOND_ATTR=1
CFLAGS_create := -DNR_THREADS=5

target-post-y := $(addprefix ${OUTPUT},$(patsubst %,%.c.s,${target-y}))
target-shell-y := list-tunables.sh

create_thread-objs := ${PTHREAD_HELPERS}
attr_setstack-3-objs := ${C_HELPERS}
attr_getdetachstate-objs := ${C_HELPERS}
attr_getinheritsched-objs := ${C_HELPERS}
attr_getschedpolicy-objs := ${C_HELPERS}
attr_init-objs := ${C_HELPERS}
create-deadline-objs := ${PTHREAD_HELPERS} ${SCHED_HELPERS}
taskset_example-objs := ${SCHED_HELPERS}
