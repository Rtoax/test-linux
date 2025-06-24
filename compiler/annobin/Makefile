# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk


include ../../compiler/compiler.mk

TARGETS :=

CC := gcc
ANNOBIN = $(shell pwd)/annobin-cc1

ifneq ($(wildcard /usr/lib/rpm/redhat/redhat-annobin-cc1),)
  $(info Found /usr/lib/rpm/redhat/redhat-annobin-cc1)
  ANNOBIN = /usr/lib/rpm/redhat/redhat-annobin-cc1
endif

feature-annobin := $(findstring 1,$(call check_compiler_option,$(CC),-specs=${ANNOBIN}))

$(info feature-annobin ${feature-annobin})
ifeq (${feature-annobin},1)
  $(info Support ANNOBIN)
  TARGETS += hello
endif


CFLAGS :=
CFLAGS += -specs=$(ANNOBIN)

LDFLAGS :=

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.s
