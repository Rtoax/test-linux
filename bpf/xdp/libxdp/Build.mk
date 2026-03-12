# SPDX-License-Identifier: GPL-3.0
__USE_TRACE_HELPERS__ := y
OUTPUT = .output/

include ansi.mk
include helpers.mk
include bpf/bpf.mk
include bpf/libxdp.mk

target-y := xsk_user

target-bpf-y := ${OUTPUT}xdp_drop.bpf.o
target-bpf-y += ${OUTPUT}xdp_xsk.bpf.o

xsk_user-objs := ${OUTPUT}libbpf_wrapper.o ${OUTPUT}libxdp_helpers.o \
		${OUTPUT}net_helpers.o ${OUTPUT}pkt_stream.o \
		${TRACE_HELPERS}

CFLAGS += -lxdp -lbpf -pthread
CFLAGS += -O0 -g -ggdb
CFLAGS += -I${OUTPUT}

CFLAGS_BPF := -I.
CFLAGS_BPF += -O2 -Wall -g -target bpf

LDFLAGS += -lxdp -lbpf
