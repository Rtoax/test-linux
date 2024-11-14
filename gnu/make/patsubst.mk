# SPDX-License-Identifier: GPL-3.0
SHELL = bash

SRCROOT = $(shell pwd)
DEPROOT = $(shell pwd)/.deps

SRCS := ${SRCROOT}/module1/a.c
SRCS += ${SRCROOT}/module1/b.c

DEPS := $(subst $(SRCROOT), $(DEPROOT), $(patsubst %.c,%.o,$(SRCS)))

.PHONY: build
build:
	echo ${DEPS}
