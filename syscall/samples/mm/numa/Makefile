# SPDX-License-Identifier: GPL-3.0
NUMAIF_HDR := /usr/include/numaif.h
ifeq ($(wildcard $(NUMAIF_HDR)),)
  $(error Not found ${NUMAIF_HDR})
endif

TARGETS :=
TARGETS += mbind
TARGETS += migrate_pages
TARGETS += get_mempolicy

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -O0
LDFLAGS += -lnuma

CFLAGS_mbind := -DALLOC_WITH_MMAP=1

include ../../../../template/main.mk

numa_helpers.o: numa_helpers.h
mbind: mbind.o numa_helpers.o
migrate_pages: migrate_pages.o
get_mempolicy: get_mempolicy.o numa_helpers.o
