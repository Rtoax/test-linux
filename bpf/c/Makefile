# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

TARGETS := hello

CC := gcc

CFLAGS :=
CFLAGS += -lbpf -lbcc

LDFLAGS :=

CFLAGS += -DDEBUG -O0 -g

LIBBPF_HEADER := /usr/include/bpf/bpf.h

ifeq ($(wildcard $(LIBBPF_HEADER)),)
  TARGETS :=
  $(warning "WARNING: You need to install libbpf headers")
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o bpf.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
