# SPDX-License-Identifier: GPL-3.0
CS_HDR_CAPSTONE = /usr/include/capstone/capstone.h

target-y :=
target-y += version
target-y += simple
target-y += detail

ifeq ($(wildcard $(CS_HDR_CAPSTONE)),)
  target-y :=
  $(warning "WARNING: You need to install capstone development")
endif

CC := gcc

CFLAGS :=
CFLAGS += -lcapstone
LDFLAGS := -lcapstone

include ../../template/main.mk

version: version.o
detail: detail.o
simple: simple.o
