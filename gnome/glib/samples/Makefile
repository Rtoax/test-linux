# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

include ../../../compiler/compiler.mk

TARGETS :=
TARGETS += gthread
TARGETS += size

CC = gcc

CFLAGS :=
LDFLAGS :=

GLIB_VERSION := glib-2.0
GLIB_LIBS := $(shell pkg-config --libs ${GLIB_VERSION})
GLIB_CFLAGS := $(shell pkg-config --cflags ${GLIB_VERSION})

$(info GLIB_CFLAGS=$(GLIB_CFLAGS))
$(info GLIB_LIBS=$(GLIB_LIBS))

CFLAGS += -Werror -Wall
CFLAGS += $(GLIB_CFLAGS)
CFLAGS += $(GLIB_LIBS)

LDFLAGS += $(GLIB_LIBS)

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
  ifneq (${CC_M32},1)
    $(error ${CC} not support -m32)
  endif
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

gthread: gthread.o
size: size.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
