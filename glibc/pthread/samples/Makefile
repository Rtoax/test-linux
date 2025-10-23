# SPDX-License-Identifier: GPL-3.0
__USE_PTHREAD_HELPERS__ = y
__USE_SCHED_HELPERS__ = y
OUTPUT := .output/

target-y :=
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

ifeq ($(shell uname -m),x86_64)
  target-y += mutex_latency
endif

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

include ../../../template/main.mk

create_thread.o: create_thread.h

foobar: ${OUTPUT}foobar.o
create_thread: ${OUTPUT}create_thread.o ${PTHREAD_HELPERS}
multi_thread_stress: ${OUTPUT}multi_thread_stress.o
dead_lock-1: ${OUTPUT}dead_lock-1.o
dead_lock-2: ${OUTPUT}dead_lock-2.o
atfork: ${OUTPUT}atfork.o
attr_setstacksize: ${OUTPUT}attr_setstacksize.o
attr_setstack-1: ${OUTPUT}attr_setstack-1.o
attr_setstack-2: ${OUTPUT}attr_setstack-2.o
attr_setstack-3: ${OUTPUT}attr_setstack-3.o
attr_setdetachstate: ${OUTPUT}attr_setdetachstate.o
attr_getstack: ${OUTPUT}attr_getstack.o
attr_getstacksize: ${OUTPUT}attr_getstacksize.o
attr_getdetachstate: ${OUTPUT}attr_getdetachstate.o
attr_getinheritsched: ${OUTPUT}attr_getinheritsched.o
attr_getschedpolicy: ${OUTPUT}attr_getschedpolicy.o
attr_init: ${OUTPUT}attr_init.o
getschedparam: ${OUTPUT}getschedparam.o
barrier_init: ${OUTPUT}barrier_init.o
cancel: ${OUTPUT}cancel.o
testcancel: ${OUTPUT}testcancel.o
setcancelstate: ${OUTPUT}setcancelstate.o
cleanup_push: ${OUTPUT}cleanup_push.o
cleanup_push-deadlock: ${OUTPUT}cleanup_push-deadlock.o
cleanup_push_defer_np: ${OUTPUT}cleanup_push_defer_np.o
create: ${OUTPUT}create.o
create-deadline: ${OUTPUT}create-deadline.o ${PTHREAD_HELPERS} ${SCHED_HELPERS}
equal: ${OUTPUT}equal.o
exit: ${OUTPUT}exit.o
key_create: ${OUTPUT}key_create.o
join-coredump: ${OUTPUT}join-coredump.o
join: ${OUTPUT}join.o
detach: ${OUTPUT}detach.o
tryjoin_np: ${OUTPUT}tryjoin_np.o
timedjoin_np: ${OUTPUT}timedjoin_np.o
getname_np: ${OUTPUT}getname_np.o
rwlock_init: ${OUTPUT}rwlock_init.o
rwlock_rdlock: ${OUTPUT}rwlock_rdlock.o
rwlockattr_setpshared: ${OUTPUT}rwlockattr_setpshared.o
setname_np: ${OUTPUT}setname_np.o
self: ${OUTPUT}self.o
setspecific: ${OUTPUT}setspecific.o
getspecific: ${OUTPUT}getspecific.o
setaffinity_np: ${OUTPUT}setaffinity_np.o
sigmask: ${OUTPUT}sigmask.o
kill: ${OUTPUT}kill.o
spin_lock: ${OUTPUT}spin_lock.o
spin-latency: ${OUTPUT}spin-latency.o
spin-latency-loop: ${OUTPUT}spin-latency-loop.o
once: ${OUTPUT}once.o
yield: ${OUTPUT}yield.o
mutexattr_setprioceiling: ${OUTPUT}mutexattr_setprioceiling.o
mutexattr_setprotocol: ${OUTPUT}mutexattr_setprotocol.o
mutexattr_setpshared: ${OUTPUT}mutexattr_setpshared.o
mutexattr_setrobust: ${OUTPUT}mutexattr_setrobust.o
mutexattr_settype: ${OUTPUT}mutexattr_settype.o
mutex_consistent: ${OUTPUT}mutex_consistent.o
mutex_getprioceiling: ${OUTPUT}mutex_getprioceiling.o
mutex_init: ${OUTPUT}mutex_init.o
mutex_latency: ${OUTPUT}mutex_latency.o
setconcurrency: ${OUTPUT}setconcurrency.o
cond_init: ${OUTPUT}cond_init.o
cond_wait: ${OUTPUT}cond_wait.o
cond_broadcast: ${OUTPUT}cond_broadcast.o
cond_broadcast-1: ${OUTPUT}cond_broadcast-1.o
cond_signal: ${OUTPUT}cond_signal.o
condattr_init: ${OUTPUT}condattr_init.o
condattr_getclock: ${OUTPUT}condattr_getclock.o
condattr_setpshared: ${OUTPUT}condattr_setpshared.o
getcpuclockid: ${OUTPUT}getcpuclockid.o
taskset_example: ${OUTPUT}taskset_example.o ${SCHED_HELPERS}
tls: ${OUTPUT}tls.o
taskset: ${OUTPUT}taskset.o
rt_thread: ${OUTPUT}rt_thread.o
cond-demo1: ${OUTPUT}cond-demo1.o
cond-demo2: ${OUTPUT}cond-demo2.o
cond-demo3-latency: ${OUTPUT}cond-demo3-latency.o
