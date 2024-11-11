# SPDX-License-Identifier: GPL-3.0
SHELL = bash

LIBS_TOPDIR := $(shell git rev-parse --show-toplevel || :)/libs/

sub-dir := rss
sub-dir += cache
sub-dir += hugepage
sub-dir += oom
sub-dir += tcmalloc
sub-dir += tlb
sub-dir += jemalloc

TARGETS := virt2phy

CC = gcc

CFLAGS :=
LDFLAGS :=

CFLAGS += -I${LIBS_TOPDIR}

CFLAGS_virt2phy := -DHAVE_MAIN=1 -DHAVE_LIB_TEST_LINUX_C=1

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: all
all: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

virt2phy: virt2phy.o libtest-linux-c.a

libtest-linux-c.a:
	@make -C ${LIBS_TOPDIR}
	@cp ${LIBS_TOPDIR}/libtest-linux-c.a $(shell pwd)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.a

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
