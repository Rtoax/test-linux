# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

TARGETS :=
TARGETS += foobar
TARGETS += pthread_atfork
TARGETS += create_thread
TARGETS += multi_thread_stress
TARGETS += dead_lock-1
TARGETS += dead_lock-2
TARGETS += pthread_attr_setstacksize
TARGETS += pthread_attr_setstack-1
TARGETS += pthread_attr_setstack-2
TARGETS += pthread_attr_setstack-3
TARGETS += pthread_attr_setdetachstate
TARGETS += pthread_attr_getstack
TARGETS += pthread_attr_getstacksize
TARGETS += pthread_attr_getdetachstate
TARGETS += pthread_attr_getinheritsched
TARGETS += pthread_attr_getschedpolicy
TARGETS += pthread_attr_init
TARGETS += pthread_barrier_init
TARGETS += pthread_cancel pthread_testcancel pthread_setcancelstate
TARGETS += pthread_create
TARGETS += pthread_create-deadline
TARGETS += pthread_cleanup_push
TARGETS += pthread_cleanup_push-deadlock
TARGETS += pthread_cleanup_push_defer_np
TARGETS += pthread_equal
TARGETS += pthread_exit
TARGETS += pthread_getschedparam
TARGETS += pthread_key_create pthread_setspecific pthread_getspecific
TARGETS += pthread_join-coredump
TARGETS += pthread_join pthread_tryjoin_np pthread_timedjoin_np pthread_detach
TARGETS += pthread_getname_np pthread_setname_np
TARGETS += pthread_rwlock_init pthread_rwlock_rdlock pthread_rwlockattr_setpshared
TARGETS += pthread_self
TARGETS += pthread_spin_lock
TARGETS += pthread_spin-latency pthread_spin-latency-loop
TARGETS += pthread_setaffinity_np
TARGETS += pthread_sigmask
TARGETS += pthread_kill
TARGETS += pthread_once
TARGETS += pthread_yield
TARGETS += pthread_mutexattr_setprioceiling
TARGETS += pthread_mutexattr_setprotocol
TARGETS += pthread_mutexattr_setpshared
TARGETS += pthread_mutexattr_setrobust
TARGETS += pthread_mutexattr_settype
TARGETS += pthread_mutex_consistent
TARGETS += pthread_mutex_getprioceiling
TARGETS += pthread_mutex_init
TARGETS += pthread_setconcurrency
TARGETS += pthread_cond_init
TARGETS += pthread_cond_wait
TARGETS += pthread_cond_broadcast pthread_cond_broadcast-1
TARGETS += pthread_cond_signal
TARGETS += pthread_condattr_init
TARGETS += pthread_condattr_getclock
TARGETS += pthread_condattr_setpshared
TARGETS += pthread_getcpuclockid
TARGETS += tls
TARGETS += taskset
TARGETS += rt_thread
TARGETS += cond-demo1 cond-demo2 cond-demo3-latency

ifeq ($(shell uname -m),x86_64)
  TARGETS += pthread_mutex_latency
endif

TARGETS += taskset_example

CC := gcc

LDFLAGS :=

# glibc >= 2.34, pthread APIs move from libpthread.so to libc.so.
# ref: https://developers.redhat.com/articles/2021/12/17/why-glibc-234-removed-libpthread
CFLAGS := -pthread
CFLAGS += -I$(shell realpath .)/../../../
ifeq (${Q}$(CC),clang)
  LDFLAGS += -Wl,-lm
else
  LDFLAGS += -lm
endif

CFLAGS += -DDEBUG -O0 -g

CFLAGS_create_thread := -DMAIN_TEST=1
CFLAGS_pthread_cond_broadcast := -DCOND_ATTR=1
CFLAGS_pthread_cond_signal := -DCOND_ATTR=1
CFLAGS_pthread_create := -DNR_THREADS=5

TARGETS_POST := $(addprefix ${OUTPUT},$(patsubst %,%.c.s,${TARGETS}))
TARGETS_POST += ld-list-tunables

include ../../../template/main.mk

ld-list-tunables:
	${Q}ld.so --list-tunables 2>/dev/null | grep -i pthread || true

pthread_helpers.o: pthread_helpers.h
sched_helpers.o: sched_helpers.h
create_thread.o: create_thread.h

foobar: ${OUTPUT}foobar.o
create_thread: ${OUTPUT}create_thread.o sys_affinity_bind.o
multi_thread_stress: ${OUTPUT}multi_thread_stress.o
dead_lock-1: ${OUTPUT}dead_lock-1.o
dead_lock-2: ${OUTPUT}dead_lock-2.o
pthread_atfork: ${OUTPUT}pthread_atfork.o
pthread_attr_setstacksize: ${OUTPUT}pthread_attr_setstacksize.o
pthread_attr_setstack-1: ${OUTPUT}pthread_attr_setstack-1.o
pthread_attr_setstack-2: ${OUTPUT}pthread_attr_setstack-2.o
pthread_attr_setstack-3: ${OUTPUT}pthread_attr_setstack-3.o
pthread_attr_setdetachstate: ${OUTPUT}pthread_attr_setdetachstate.o
pthread_attr_getstack: ${OUTPUT}pthread_attr_getstack.o
pthread_attr_getstacksize: ${OUTPUT}pthread_attr_getstacksize.o
pthread_attr_getdetachstate: ${OUTPUT}pthread_attr_getdetachstate.o
pthread_attr_getinheritsched: ${OUTPUT}pthread_attr_getinheritsched.o
pthread_attr_getschedpolicy: ${OUTPUT}pthread_attr_getschedpolicy.o
pthread_attr_init: ${OUTPUT}pthread_attr_init.o
pthread_getschedparam: ${OUTPUT}pthread_getschedparam.o
pthread_barrier_init: ${OUTPUT}pthread_barrier_init.o
pthread_cancel: ${OUTPUT}pthread_cancel.o
pthread_testcancel: ${OUTPUT}pthread_testcancel.o
pthread_setcancelstate: ${OUTPUT}pthread_setcancelstate.o
pthread_cleanup_push: ${OUTPUT}pthread_cleanup_push.o
pthread_cleanup_push-deadlock: ${OUTPUT}pthread_cleanup_push-deadlock.o
pthread_cleanup_push_defer_np: ${OUTPUT}pthread_cleanup_push_defer_np.o
pthread_create: ${OUTPUT}pthread_create.o
pthread_create-deadline: ${OUTPUT}pthread_create-deadline.o pthread_helpers.o sched_helpers.o
pthread_equal: ${OUTPUT}pthread_equal.o
pthread_exit: ${OUTPUT}pthread_exit.o
pthread_key_create: ${OUTPUT}pthread_key_create.o
pthread_join-coredump: ${OUTPUT}pthread_join-coredump.o
pthread_join: ${OUTPUT}pthread_join.o
pthread_detach: ${OUTPUT}pthread_detach.o
pthread_tryjoin_np: ${OUTPUT}pthread_tryjoin_np.o
pthread_timedjoin_np: ${OUTPUT}pthread_timedjoin_np.o
pthread_getname_np: ${OUTPUT}pthread_getname_np.o
pthread_rwlock_init: ${OUTPUT}pthread_rwlock_init.o
pthread_rwlock_rdlock: ${OUTPUT}pthread_rwlock_rdlock.o
pthread_rwlockattr_setpshared: ${OUTPUT}pthread_rwlockattr_setpshared.o
pthread_setname_np: ${OUTPUT}pthread_setname_np.o
pthread_self: ${OUTPUT}pthread_self.o
pthread_setspecific: ${OUTPUT}pthread_setspecific.o
pthread_getspecific: ${OUTPUT}pthread_getspecific.o
pthread_setaffinity_np: ${OUTPUT}pthread_setaffinity_np.o
pthread_sigmask: ${OUTPUT}pthread_sigmask.o
pthread_kill: ${OUTPUT}pthread_kill.o
pthread_spin_lock: ${OUTPUT}pthread_spin_lock.o
pthread_spin-latency: ${OUTPUT}pthread_spin-latency.o
pthread_spin-latency-loop: ${OUTPUT}pthread_spin-latency-loop.o
pthread_once: ${OUTPUT}pthread_once.o
pthread_yield: ${OUTPUT}pthread_yield.o
pthread_mutexattr_setprioceiling: ${OUTPUT}pthread_mutexattr_setprioceiling.o
pthread_mutexattr_setprotocol: ${OUTPUT}pthread_mutexattr_setprotocol.o
pthread_mutexattr_setpshared: ${OUTPUT}pthread_mutexattr_setpshared.o
pthread_mutexattr_setrobust: ${OUTPUT}pthread_mutexattr_setrobust.o
pthread_mutexattr_settype: ${OUTPUT}pthread_mutexattr_settype.o
pthread_mutex_consistent: ${OUTPUT}pthread_mutex_consistent.o
pthread_mutex_getprioceiling: ${OUTPUT}pthread_mutex_getprioceiling.o
pthread_mutex_init: ${OUTPUT}pthread_mutex_init.o
pthread_mutex_latency: ${OUTPUT}pthread_mutex_latency.o
pthread_setconcurrency: ${OUTPUT}pthread_setconcurrency.o
pthread_cond_init: ${OUTPUT}pthread_cond_init.o
pthread_cond_wait: ${OUTPUT}pthread_cond_wait.o
pthread_cond_broadcast: ${OUTPUT}pthread_cond_broadcast.o
pthread_cond_broadcast-1: ${OUTPUT}pthread_cond_broadcast-1.o
pthread_cond_signal: ${OUTPUT}pthread_cond_signal.o
pthread_condattr_init: ${OUTPUT}pthread_condattr_init.o
pthread_condattr_getclock: ${OUTPUT}pthread_condattr_getclock.o
pthread_condattr_setpshared: ${OUTPUT}pthread_condattr_setpshared.o
pthread_getcpuclockid: ${OUTPUT}pthread_getcpuclockid.o
taskset_example: ${OUTPUT}taskset_example.o sched_helpers.o
tls: ${OUTPUT}tls.o
taskset: ${OUTPUT}taskset.o
rt_thread: ${OUTPUT}rt_thread.o
cond-demo1: ${OUTPUT}cond-demo1.o
cond-demo2: ${OUTPUT}cond-demo2.o
cond-demo3-latency: ${OUTPUT}cond-demo3-latency.o
