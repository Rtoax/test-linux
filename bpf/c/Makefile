# SPDX-License-Identifier: GPL-3.0
TARGETS := hello

LDFLAGS := -lbpf -lbcc

include ../../template/main.mk

hello: hello.o bpf.o
