# SPDX-License-Identifier: GPL-3.0
SHELL = bash

CC := gcc

CFLAGS :=
LDFLAGS :=

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
TARGETS += __atomic_always_lock_free
TARGETS += __atomic_is_lock_free

ifdef M32
  CFLAGS += -m32
endif

CFLAGS_load-store := -DTEST_C_RAW=1
CFLAGS_load-store-atomic-relaxed := -DTEST_ATOMIC_RELAXED=1
CFLAGS_load-store-atomic-strict := -DTEST_ATOMIC_STRICT=1
# Choice this macro
CFLAGS___atomic_thread_fence := -DHAVE___atomic_thread_fence__ATOMIC_ACQ_REL=1
CFLAGS___atomic_always_lock_free := -latomic
CFLAGS___atomic_is_lock_free := -latomic

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
