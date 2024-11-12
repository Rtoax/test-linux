# SPDX-License-Identifier: GPL-3.0
SHELL = bash

CC = gcc

LIBS_TOPDIR := $(shell git rev-parse --show-toplevel || :)/libs/

TARGETS := dl_iterate_phdr
TARGETS += dl_iterate_phdr-pie
TARGETS += has_shared_object

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -I${LIBS_TOPDIR}

LDFLAGS :=

CFLAGS_dl_iterate_phdr := -no-pie
CFLAGS_dl_iterate_phdr-pie := -fpie
LDFLAGS_dl_iterate_phdr-pie := -pie

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

dl_iterate_phdr: dl_iterate_phdr.o libtest-linux-c.a
dl_iterate_phdr-pie: dl_iterate_phdr-pie.o libtest-linux-c.a
has_shared_object: has_shared_object.o

libtest-linux-c.a:
	@make -C ${LIBS_TOPDIR} $(@)
	@cp ${LIBS_TOPDIR}/libtest-linux-c.a $(shell pwd)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.a
