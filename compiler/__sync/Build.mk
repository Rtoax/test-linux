# SPDX-License-Identifier: GPL-3.0
target-y := atomic_test
target-y += __sync_fetch_and_add
target-y += __sync_fetch_and_sub
target-y += __sync_fetch_and_or
target-y += __sync_fetch_and_and
target-y += __sync_fetch_and_xor
target-y += __sync_fetch_and_nand
target-y += __sync_add_and_fetch
target-y += __sync_sub_and_fetch
target-y += __sync_or_and_fetch
target-y += __sync_and_and_fetch
target-y += __sync_xor_and_fetch
target-y += __sync_nand_and_fetch
target-y += __sync_val_compare_and_swap
target-y += __sync_bool_compare_and_swap
target-y += __sync_lock_test_and_set
target-y += __sync_lock_release
target-y += __sync_synchronize
target-${IS_X86_64} += spin-demo3 spin-demo3-nonlock

CFLAGS_spin-demo3-nonlock := -DNONLOCK=1
# Warn when "__sync_fetch_and_nand" and "__sync_nand_and_fetch" built-in
# functions are used.  These functions changed semantics in GCC 4.4.
CFLAGS___sync_nand_and_fetch := -Wsync-nand

LDFLAGS += -lpthread
