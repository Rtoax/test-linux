# SPDX-License-Identifier: GPL-3.0
SHELL = bash

include ../../../../tlbuild.mk

NUMAIF_HDR = /usr/include/numaif.h

TARGETS :=
TARGETS += mbind
TARGETS += migrate_pages
TARGETS += get_mempolicy

ifeq ($(wildcard $(NUMAIF_HDR)),)
  $(error Not found ${NUMAIF_HDR})
endif

CC = gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -O0

CFLAGS_get_mempolicy := -lnuma
CFLAGS_migrate_pages := -lnuma
CFLAGS_mbind := -lnuma -DALLOC_WITH_MMAP=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

mbind: mbind.o helpers.o
migrate_pages: migrate_pages.o
get_mempolicy: get_mempolicy.o helpers.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

