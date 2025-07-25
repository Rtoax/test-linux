# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets :=
targets += foobar
targets += pthread_atfork
targets += create_thread
targets += multi_thread_stress
targets += dead_lock-1
targets += dead_lock-2
targets += pthread_attr_setstacksize
targets += pthread_attr_setstack-1
targets += pthread_attr_setstack-2
targets += pthread_attr_setstack-3
targets += pthread_attr_setdetachstate
targets += pthread_attr_getstack
targets += pthread_attr_getstacksize
targets += pthread_attr_getdetachstate
targets += pthread_attr_getinheritsched
targets += pthread_attr_getschedpolicy
targets += pthread_attr_init
targets += pthread_barrier_init
targets += pthread_cancel pthread_testcancel pthread_setcancelstate
targets += pthread_create
targets += pthread_create-deadline
targets += pthread_cleanup_push
targets += pthread_cleanup_push-deadlock
targets += pthread_cleanup_push_defer_np
targets += pthread_equal
targets += pthread_exit
targets += pthread_getschedparam
targets += pthread_key_create pthread_setspecific pthread_getspecific
targets += pthread_join-coredump
targets += pthread_join pthread_tryjoin_np pthread_timedjoin_np pthread_detach
targets += pthread_getname_np pthread_setname_np
targets += pthread_rwlock_init pthread_rwlock_rdlock pthread_rwlockattr_setpshared
targets += pthread_self
targets += pthread_spin_lock
targets += pthread_spin-latency pthread_spin-latency-loop
targets += pthread_setaffinity_np
targets += pthread_sigmask
targets += pthread_kill
targets += pthread_once
targets += pthread_yield
targets += pthread_mutexattr_setprioceiling
targets += pthread_mutexattr_setprotocol
targets += pthread_mutexattr_setpshared
targets += pthread_mutexattr_setrobust
targets += pthread_mutexattr_settype
targets += pthread_mutex_consistent
targets += pthread_mutex_getprioceiling
targets += pthread_mutex_init
targets += pthread_setconcurrency
targets += pthread_cond_init
targets += pthread_cond_wait
targets += pthread_cond_broadcast pthread_cond_broadcast-1
targets += pthread_cond_signal
targets += pthread_condattr_init
targets += pthread_condattr_getclock
targets += pthread_condattr_setpshared
targets += pthread_getcpuclockid
targets += tls
targets += taskset
targets += rt_thread
targets += cond-demo1 cond-demo2 cond-demo3-latency

ifeq ($(shell uname -m),x86_64)
  targets += pthread_mutex_latency
endif

targets += taskset_example

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

CFLAGS_create_thread := -DMAIN_TEST=1
CFLAGS_pthread_cond_broadcast := -DCOND_ATTR=1
CFLAGS_pthread_cond_signal := -DCOND_ATTR=1
CFLAGS_pthread_create := -DNR_THREADS=5

targets-post := $(addprefix ${OUTPUT},$(patsubst %,%.c.s,${targets}))
targets-post += ld-list-tunables

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
