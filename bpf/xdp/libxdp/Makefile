# SPDX-License-Identifier: GPL-3.0
include ../../bpf.mk

targets := xsk_user

targets-bpf := xdp_drop.bpf.o
targets-bpf += xdp_xsk.bpf.o

CFLAGS :=
CFLAGS += -lxdp -lbpf -pthread
CFLAGS += -O0 -g -ggdb

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

LDFLAGS :=
LDFLAGS += -lxdp -lbpf

include ../../../template/main.mk

xdp_xsk.bpf.o: vmlinux.h
xdp_drop.bpf.o: vmlinux.h
xdp_xsk.o: xdp_xsk.skel.h
xsk_user.o: xdp_xsk.skel.h
xsk_user: xsk_user.o libbpf_wrapper.o libxdp_helpers.o trace_helpers.o \
	net_helpers.o pkt_stream.o

include ../../bpftool/vmlinux.h.mk
