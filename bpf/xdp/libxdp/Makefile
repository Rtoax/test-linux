# SPDX-License-Identifier: GPL-3.0

SHELL = /bin/bash

ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../../bpf.mk

TARGETS :=
TARGETS_BPF :=

TARGETS_BPF += xdp_drop.bpf.o

CC := gcc
CLANG := clang
BPFTOOL := bpftool

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -lxdp

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

LDFLAGS :=
LDFLAGS += -lxdp

.PHONY: build
.PHONY: build
build: vmlinux.h ${TARGETS_BPF} ${TARGETS}
	@echo -e "  \033[1;33mDone\033[m"

# Add more object.o file

%.bpf.o: %.bpf.c vmlinux.h
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(Q)$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	$(Q)$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1m$(@)\033[m"
	${Q}${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	$(Q)rm -f ${TARGETS} *.o vmlinux.h
