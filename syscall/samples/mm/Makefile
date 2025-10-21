# SPDX-License-Identifier: GPL-3.0
sub-dir :=
sub-dir += mmap
sub-dir += madvise
sub-dir += memfd
sub-dir += numa

target-y :=
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

CFLAGS :=
CFLAGS += -pthread
CFLAGS += -lrt

include ../../../template/main.mk

brk: brk.o
sbrk: sbrk.o
sbrk-bss: sbrk-bss.o
membarrier: membarrier.o
mlock: mlock.o
mlockall: mlockall.o
pkey_alloc: pkey_alloc.o
pkey_free: pkey_free.o
pkey_mprotect: pkey_mprotect.o
mprotect: mprotect.o
mprotect-ld: mprotect-ld.o
process_madvise: process_madvise.o
process_mrelease: process_mrelease.o
