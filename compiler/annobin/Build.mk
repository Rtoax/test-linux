# SPDX-License-Identifier: GPL-3.0
include compiler.mk

ANNOBIN := $(shell pwd)/annobin-cc1
ANNOCHECK := annocheck

ifneq ($(wildcard /usr/lib/rpm/redhat/redhat-annobin-cc1),)
  $(info Found /usr/lib/rpm/redhat/redhat-annobin-cc1)
  ANNOBIN := /usr/lib/rpm/redhat/redhat-annobin-cc1
endif

feature-annobin := $(call compiler_support_option,$(CC),-specs=${ANNOBIN})

$(info feature-annobin ${feature-annobin})
ifeq (${feature-annobin},y)
  $(info Support ANNOBIN)
  target-y += hello
endif

target-post-y := $(patsubst %,%.annocheck.log,$(target-y))

CFLAGS += -specs=$(ANNOBIN)
