# SPDX-License-Identifier: GPL-3.0
SHELL = /bin/bash

NUMAIF_HDR = /usr/include/numaif.h

sub-dir :=
sub-dir += mmap
sub-dir += madvise
sub-dir += memfd

TARGETS :=
TARGETS += brk sbrk sbrk-bss
TARGETS += membarrier
TARGETS += mlock mlockall
TARGETS += pkey_alloc
TARGETS += pkey_free
TARGETS += pkey_mprotect
TARGETS += mprotect
TARGETS += mprotect-ld
ifneq ($(wildcard $(NUMAIF_HDR)),)
  TARGETS += mbind
  TARGETS += migrate_pages
  TARGETS += get_mempolicy
endif
TARGETS += process_madvise
TARGETS += process_mrelease

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -lrt
CFLAGS += -DDEBUG -O0 -g

CFLAGS_get_mempolicy := -lnuma

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

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
mbind: mbind.o
migrate_pages: migrate_pages.o
get_mempolicy: get_mempolicy.o
process_madvise: process_madvise.o
process_mrelease: process_mrelease.o

CFLAGS_migrate_pages := -lnuma

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=) CC=$(CC) CXX=$(CXX)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
