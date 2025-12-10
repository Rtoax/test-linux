# SPDX-License-Identifier: GPL-3.0
include libatomic.mk

target-y :=
target-y += test1
target-y += load-store
target-y += load-store-atomic-relaxed
target-y += load-store-atomic-strict
target-y += exchange
target-y += compare_exchange
target-y += fetch
target-y += __ATOMIC_
target-y += test_and_set
target-y += clear
target-y += thread_fence
target-y += signal_fence
target-${HAVE_LIBATOMIC} += always_lock_free
target-${HAVE_LIBATOMIC} += is_lock_free

CFLAGS += -pthread

CFLAGS_load-store := -DTEST_C_RAW=1
CFLAGS_load-store-atomic-relaxed := -DTEST_ATOMIC_RELAXED=1
CFLAGS_load-store-atomic-strict := -DTEST_ATOMIC_STRICT=1
# Choice this macro
CFLAGS_thread_fence := -DHAVE_thread_fence__ATOMIC_ACQ_REL=1
LDFLAGS_always_lock_free := -latomic
LDFLAGS_is_lock_free := -latomic

include main.mk

test1: test1.o
load-store: load-store.o
load-store-atomic-relaxed: load-store-atomic-relaxed.o
load-store-atomic-strict: load-store-atomic-strict.o
exchange: exchange.o
compare_exchange: compare_exchange.o
fetch: fetch.o
__ATOMIC_: __ATOMIC_.o
test_and_set: test_and_set.o
clear: clear.o
thread_fence: thread_fence.o
signal_fence: signal_fence.o
always_lock_free: always_lock_free.o
is_lock_free: is_lock_free.o
