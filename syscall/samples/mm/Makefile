# SPDX-License-Identifier: GPL-3.0
sub-dir :=
sub-dir += mmap
sub-dir += madvise
sub-dir += memfd
sub-dir += numa

TARGETS :=
TARGETS += brk sbrk sbrk-bss
TARGETS += membarrier
TARGETS += mlock mlockall
TARGETS += pkey_alloc
TARGETS += pkey_free
TARGETS += pkey_mprotect
TARGETS += mprotect
TARGETS += mprotect-ld
TARGETS += process_madvise
TARGETS += process_mrelease

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
