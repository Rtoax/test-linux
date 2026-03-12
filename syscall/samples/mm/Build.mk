# SPDX-License-Identifier: GPL-3.0
subdir-y += mmap
subdir-y += madvise
subdir-y += memfd
subdir-y += numa

target-y += brk sbrk sbrk-bss
target-y += membarrier
target-y += mlock mlockall
target-y += pkey_alloc
target-y += pkey_free
target-y += pkey_mprotect
target-y += mprotect
target-y += mprotect-ld
target-y += process_madvise
target-y += process_mrelease

CFLAGS += -pthread
CFLAGS += -lrt
