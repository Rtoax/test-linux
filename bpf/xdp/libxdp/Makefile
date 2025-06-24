# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk
include ../../bpf.mk

TARGETS :=
TARGETS_BPF :=

TARGETS += xsk_user

TARGETS_BPF += xdp_drop.bpf.o
TARGETS_BPF += xdp_xsk.bpf.o

CC := gcc
CLANG := clang
BPFTOOL := bpftool

CFLAGS :=
CFLAGS += -lxdp -lbpf -pthread
CFLAGS += -O0 -g -ggdb

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

LDFLAGS :=
LDFLAGS += -lxdp -lbpf

# Never append to skel target, always generate by bpf target
TARGETS_SKEL := $(patsubst %.bpf.o,%.skel.h,$(TARGETS_BPF))

.PHONY: build
build: vmlinux.h ${TARGETS_BPF} ${TARGETS_SKEL} ${TARGETS}
	@echo -e "  \033[1;33mDone\033[m"

xsk_user: xsk_user.o libbpf_wrapper.o libxdp_helpers.o trace_helpers.o \
	net_helpers.o pkt_stream.o

%.bpf.o: %.bpf.c vmlinux.h
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

%.skel.h: %.bpf.o
	@echo -e "  SKEL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(BPFTOOL) gen skeleton $< > $@

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(Q)$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	$(Q)$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

include ../../bpftool/vmlinux.h.mk

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_BPF) $(TARGETS_SKEL)\033[m"
	$(Q)rm -f ${TARGETS} ${TARGETS_BPF} ${TARGETS_SKEL} *.o vmlinux.h
