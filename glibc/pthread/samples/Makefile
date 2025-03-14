# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

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
CFLAGS := -Werror -Wall -pthread
CFLAGS += -Wstrict-prototypes
CFLAGS += -I$(shell realpath .)/../../../
ifeq (${Q}$(CC),clang)
  LDFLAGS += -Wl,-lm
else
  CFLAGS += -lm
endif

CFLAGS += -DDEBUG -O0 -g

CFLAGS_create_thread := -DMAIN_TEST=1
CFLAGS_pthread_cond_broadcast := -DCOND_ATTR=1
CFLAGS_pthread_cond_signal := -DCOND_ATTR=1
CFLAGS_pthread_create := -DNR_THREADS=5

build: ${TARGETS}
	${Q}ld.so --list-tunables 2>/dev/null | grep -i pthread || true
	@echo -e " \033[1;33m Done \033[m"

foobar: foobar.o
create_thread: create_thread.o sys_affinity_bind.o
multi_thread_stress: multi_thread_stress.o
dead_lock-1: dead_lock-1.o
dead_lock-2: dead_lock-2.o
pthread_atfork: pthread_atfork.o
pthread_attr_setstacksize: pthread_attr_setstacksize.o
pthread_attr_setstack-1: pthread_attr_setstack-1.o
pthread_attr_setstack-2: pthread_attr_setstack-2.o
pthread_attr_setstack-3: pthread_attr_setstack-3.o
pthread_attr_setdetachstate: pthread_attr_setdetachstate.o
pthread_attr_getstack: pthread_attr_getstack.o
pthread_attr_getstacksize: pthread_attr_getstacksize.o
pthread_attr_getdetachstate: pthread_attr_getdetachstate.o
pthread_attr_getinheritsched: pthread_attr_getinheritsched.o
pthread_attr_getschedpolicy: pthread_attr_getschedpolicy.o
pthread_attr_init: pthread_attr_init.o
pthread_getschedparam: pthread_getschedparam.o
pthread_barrier_init: pthread_barrier_init.o
pthread_cancel: pthread_cancel.o
pthread_testcancel: pthread_testcancel.o
pthread_setcancelstate: pthread_setcancelstate.o
pthread_cleanup_push: pthread_cleanup_push.o
pthread_cleanup_push-deadlock: pthread_cleanup_push-deadlock.o
pthread_cleanup_push_defer_np: pthread_cleanup_push_defer_np.o
pthread_create: pthread_create.o
pthread_create-deadline: pthread_create-deadline.o
pthread_equal: pthread_equal.o
pthread_exit: pthread_exit.o
pthread_key_create: pthread_key_create.o
pthread_join-coredump: pthread_join-coredump.o
pthread_join: pthread_join.o
pthread_detach: pthread_detach.o
pthread_tryjoin_np: pthread_tryjoin_np.o
pthread_timedjoin_np: pthread_timedjoin_np.o
pthread_getname_np: pthread_getname_np.o
pthread_rwlock_init: pthread_rwlock_init.o
pthread_rwlock_rdlock: pthread_rwlock_rdlock.o
pthread_rwlockattr_setpshared: pthread_rwlockattr_setpshared.o
pthread_setname_np: pthread_setname_np.o
pthread_self: pthread_self.o
pthread_setspecific: pthread_setspecific.o
pthread_getspecific: pthread_getspecific.o
pthread_setaffinity_np: pthread_setaffinity_np.o
pthread_sigmask: pthread_sigmask.o
pthread_kill: pthread_kill.o
pthread_spin_lock: pthread_spin_lock.o
pthread_spin-latency: pthread_spin-latency.o
pthread_spin-latency-loop: pthread_spin-latency-loop.o
pthread_once: pthread_once.o
pthread_yield: pthread_yield.o
pthread_mutexattr_setprioceiling: pthread_mutexattr_setprioceiling.o
pthread_mutexattr_setprotocol: pthread_mutexattr_setprotocol.o
pthread_mutexattr_setpshared: pthread_mutexattr_setpshared.o
pthread_mutexattr_setrobust: pthread_mutexattr_setrobust.o
pthread_mutexattr_settype: pthread_mutexattr_settype.o
pthread_mutex_consistent: pthread_mutex_consistent.o
pthread_mutex_getprioceiling: pthread_mutex_getprioceiling.o
pthread_mutex_init: pthread_mutex_init.o
pthread_mutex_latency: pthread_mutex_latency.o
pthread_setconcurrency: pthread_setconcurrency.o
pthread_cond_init: pthread_cond_init.o
pthread_cond_wait: pthread_cond_wait.o
pthread_cond_broadcast: pthread_cond_broadcast.o
pthread_cond_broadcast-1: pthread_cond_broadcast-1.o
pthread_cond_signal: pthread_cond_signal.o
pthread_condattr_init: pthread_condattr_init.o
pthread_condattr_getclock: pthread_condattr_getclock.o
pthread_condattr_setpshared: pthread_condattr_setpshared.o
pthread_getcpuclockid: pthread_getcpuclockid.o
taskset_example: taskset_example.o helpers.o
tls: tls.o
taskset: taskset.o
rt_thread: rt_thread.o
cond-demo1: cond-demo1.o
cond-demo2: cond-demo2.o
cond-demo3-latency: cond-demo3-latency.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.log *.s
