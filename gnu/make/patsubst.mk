# SPDX-License-Identifier: GPL-3.0
SHELL = bash

SRCROOT = $(shell pwd)
DEPROOT = $(shell pwd)/.deps

SRCS := ${SRCROOT}/module1/a.c
SRCS += ${SRCROOT}/module1/b.c

# $(patsubst <pattern>,<replacement>,<text>)
OBJS := $(patsubst %.c,%.o,$(SRCS))
# equal to:
OBJS_2 := $(SRCS:.c=.o)

# $(subst <from>,<to>,<text>)
DEPS := $(subst $(SRCROOT),$(DEPROOT),$(OBJS))

.PHONY: build
build:
	@echo OBJS=${OBJS}
	@echo OBJS_2=${OBJS_2}
	@echo DEPS=${DEPS}
