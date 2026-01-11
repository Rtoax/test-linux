# SPDX-License-Identifier: GPL-3.0
SRCROOT := $(shell pwd)
DEPROOT := $(shell pwd)/.deps

SRCS := ${SRCROOT}/module1/obj-a.c
SRCS += ${SRCROOT}/module1/obj-b.c

# $(patsubst <pattern>,<replacement>,<text>)
OBJS := $(patsubst %.c,%.o,$(SRCS))
# equal to:
OBJS_2 := $(SRCS:.c=.o)

# $(subst <from>,<to>,<text>)
DEPS := $(subst $(SRCROOT),$(DEPROOT),$(OBJS))
DEPS_NAMES := $(subst -,_,$(DEPS))

.PHONY: build
build:
	@echo OBJS=${OBJS}
	@echo OBJS_2=${OBJS_2}
	@echo DEPS=${DEPS}
	@echo DEPS_NAMES=${DEPS_NAMES}
