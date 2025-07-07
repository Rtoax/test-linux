# SPDX-License-Identifier: GPL-3.0
TARGETS := hello

LDFLAGS := -lbpf -lbcc

include ../../template/main.mk

bpf_helpers.o: bpf_helpers.h
hello: hello.o bpf_helpers.o
