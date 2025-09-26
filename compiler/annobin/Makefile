# SPDX-License-Identifier: GPL-3.0
include ../../compiler/compiler.mk

targets :=
ANNOBIN := $(shell pwd)/annobin-cc1
ANNOCHECK := annocheck

ifneq ($(wildcard /usr/lib/rpm/redhat/redhat-annobin-cc1),)
  $(info Found /usr/lib/rpm/redhat/redhat-annobin-cc1)
  ANNOBIN := /usr/lib/rpm/redhat/redhat-annobin-cc1
endif

feature-annobin := $(findstring 1,$(call check_compiler_option,$(CC),-specs=${ANNOBIN}))

$(info feature-annobin ${feature-annobin})
ifeq (${feature-annobin},1)
  $(info Support ANNOBIN)
  targets += hello
endif

targets-post := $(patsubst %,%.annocheck.log,$(targets))

CFLAGS += -specs=$(ANNOBIN)

include ../../template/main.mk

hello: hello.o

%.annocheck.log: %
	${Q}${ANNOCHECK} ${^} | tee ${@}
