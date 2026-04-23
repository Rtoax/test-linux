# SPDX-License-Identifier: GPL-3.0
include helpers.mk
include bpf/bpf.mk
include bpf/libxdp.mk

target-y := xsk_user

target-bpf-y := xdp_hello.bpf.o
target-bpf-y += xdp_count.bpf.o
target-bpf-y += xdp_elfsec.bpf.o
target-bpf-y += xdp_drop.bpf.o
target-bpf-y += xdp_xsk.bpf.o

target-post-y += post-xdp_elfsec
target-post-y += post-xdp_drop

xsk_user-objs := libbpf_wrapper.o libxdp_helpers.o \
		net_helpers.o pkt_stream.o \
		${TRACE_HELPERS}

CFLAGS += -I${OUTPUT}
CFLAGS_BPF := -I.

LDFLAGS += -lxdp -lbpf
