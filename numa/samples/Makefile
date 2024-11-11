# SPDX-License-Identifier: GPL-3.0
SHELL = bash

LIBNUMA_HDR = /usr/include/numa.h

TARGETS :=
TARGETS += numa_alloc
TARGETS += numa_available
TARGETS += numa_max_node
TARGETS += numa_max_possible_node
TARGETS += numa_node_size64
TARGETS += numa_node_size
TARGETS += numa_pagesize
TARGETS += numa_preferred
TARGETS += migrate_pages

CC = gcc

ifeq ($(wildcard $(LIBNUMA_HDR)),)
  TARGETS :=
  $(warning "ERROR: Must install numactl development header")
endif

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lnuma

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

numa_alloc: numa_alloc.o
numa_available: numa_available.o
numa_max_node: numa_max_node.o
numa_max_possible_node: numa_max_possible_node.o
numa_node_size64: numa_node_size64.o
numa_node_size: numa_node_size.o
numa_pagesize: numa_pagesize.o
numa_preferred: numa_preferred.o
migrate_pages: migrate_pages.o

# FIXME:
CFLAGS_numa_node_size := -Wno-incompatible-pointer-types

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
