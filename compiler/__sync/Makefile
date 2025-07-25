# SPDX-License-Identifier: GPL-3.0
targets := atomic_test
targets += __sync_fetch_and_add
targets += __sync_fetch_and_sub
targets += __sync_fetch_and_or
targets += __sync_fetch_and_and
targets += __sync_fetch_and_xor
targets += __sync_fetch_and_nand
targets += __sync_add_and_fetch
targets += __sync_sub_and_fetch
targets += __sync_or_and_fetch
targets += __sync_and_and_fetch
targets += __sync_xor_and_fetch
targets += __sync_nand_and_fetch
targets += __sync_val_compare_and_swap
targets += __sync_bool_compare_and_swap
targets += __sync_lock_test_and_set
targets += __sync_lock_release
targets += __sync_synchronize
ifeq ($(shell uname -m),x86_64)
  targets += spin-demo3 spin-demo3-nonlock
endif

CFLAGS :=
CFLAGS += -lpthread
CFLAGS_spin-demo3-nonlock := -DNONLOCK=1
# Warn when "__sync_fetch_and_nand" and "__sync_nand_and_fetch" built-in
# functions are used.  These functions changed semantics in GCC 4.4.
CFLAGS___sync_nand_and_fetch := -Wsync-nand

include ../../template/main.mk

__sync_fetch_and_add: __sync_fetch_and_add.o
__sync_fetch_and_sub: __sync_fetch_and_sub.o
__sync_fetch_and_or: __sync_fetch_and_or.o
__sync_fetch_and_and: __sync_fetch_and_and.o
__sync_fetch_and_xor: __sync_fetch_and_xor.o
__sync_fetch_and_nand: __sync_fetch_and_nand.o
__sync_add_and_fetch: __sync_add_and_fetch.o
__sync_sub_and_fetch: __sync_sub_and_fetch.o
__sync_or_and_fetch: __sync_or_and_fetch.o
__sync_and_and_fetch: __sync_and_and_fetch.o
__sync_xor_and_fetch: __sync_xor_and_fetch.o
__sync_nand_and_fetch: __sync_nand_and_fetch.o
__sync_val_compare_and_swap: __sync_val_compare_and_swap.o
__sync_bool_compare_and_swap: __sync_bool_compare_and_swap.o
__sync_lock_test_and_set: __sync_lock_test_and_set.o
__sync_synchronize: __sync_synchronize.o
__sync_lock_release: __sync_lock_release.o
atomic_test: atomic_test.o
spin-demo3: spin-demo3.o
spin-demo3-nonlock: spin-demo3-nonlock.o
