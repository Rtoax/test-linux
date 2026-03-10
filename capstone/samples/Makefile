# SPDX-License-Identifier: GPL-3.0
CS_HDR_CAPSTONE = /usr/include/capstone/capstone.h

target-y += version
target-y += simple
target-y += detail

ifeq ($(wildcard $(CS_HDR_CAPSTONE)),)
  target-y :=
  $(warning "WARNING: You need to install capstone development")
endif

CFLAGS += -lcapstone
LDFLAGS := -lcapstone

include main.mk
