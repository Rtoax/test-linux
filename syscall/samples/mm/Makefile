# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


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

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -lrt
CFLAGS += -DDEBUG -O0 -g

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

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
process_madvise: process_madvise.o
process_mrelease: process_mrelease.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=) CC=$(CC) CXX=$(CXX)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
