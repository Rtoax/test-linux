# SPDX-License-Identifier: GPL-3.0
CS_HDR_CAPSTONE = /usr/include/capstone/capstone.h

TARGETS :=
TARGETS += version
TARGETS += simple
TARGETS += detail

ifeq ($(wildcard $(CS_HDR_CAPSTONE)),)
  TARGETS :=
  $(warning "WARNING: You need to install capstone development")
endif

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -lcapstone
LDFLAGS := -lcapstone

include ../../template/main.mk

version: version.o
detail: detail.o
simple: simple.o
