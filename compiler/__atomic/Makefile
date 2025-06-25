# SPDX-License-Identifier: GPL-3.0
HAVE_LIBATOMIC := $(shell ldconfig -p | grep -w libatomic.so 2>/dev/null)
TARGETS :=
TARGETS += test1
TARGETS += load-store
TARGETS += load-store-atomic-relaxed
TARGETS += load-store-atomic-strict
TARGETS += exchange
TARGETS += compare_exchange
TARGETS += fetch
TARGETS += __ATOMIC_
TARGETS += __atomic_test_and_set
TARGETS += __atomic_clear
TARGETS += __atomic_thread_fence
TARGETS += __atomic_signal_fence

ifneq (${HAVE_LIBATOMIC},)
  $(info Found libatomic.so)
  TARGETS += __atomic_always_lock_free
  TARGETS += __atomic_is_lock_free
endif

CFLAGS += -pthread

CFLAGS_load-store := -DTEST_C_RAW=1
CFLAGS_load-store-atomic-relaxed := -DTEST_ATOMIC_RELAXED=1
CFLAGS_load-store-atomic-strict := -DTEST_ATOMIC_STRICT=1
# Choice this macro
CFLAGS___atomic_thread_fence := -DHAVE___atomic_thread_fence__ATOMIC_ACQ_REL=1
LDFLAGS___atomic_always_lock_free := -latomic
LDFLAGS___atomic_is_lock_free := -latomic

include ../../template/main.mk

test1: test1.o
load-store: load-store.o
load-store-atomic-relaxed: load-store-atomic-relaxed.o
load-store-atomic-strict: load-store-atomic-strict.o
exchange: exchange.o
compare_exchange: compare_exchange.o
fetch: fetch.o
__ATOMIC_: __ATOMIC_.o
__atomic_test_and_set: __atomic_test_and_set.o
__atomic_clear: __atomic_clear.o
__atomic_thread_fence: __atomic_thread_fence.o
__atomic_signal_fence: __atomic_signal_fence.o
__atomic_always_lock_free: __atomic_always_lock_free.o
__atomic_is_lock_free: __atomic_is_lock_free.o
