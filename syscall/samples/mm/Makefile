# SPDX-License-Identifier: GPL-3.0
sub-dir :=
sub-dir += mmap
sub-dir += madvise
sub-dir += memfd
sub-dir += numa

targets :=
targets += brk sbrk sbrk-bss
targets += membarrier
targets += mlock mlockall
targets += pkey_alloc
targets += pkey_free
targets += pkey_mprotect
targets += mprotect
targets += mprotect-ld
targets += process_madvise
targets += process_mrelease

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
