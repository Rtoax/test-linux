# SPDX-License-Identifier: GPL-3.0
include ../../../compiler/compiler.mk

target-y :=
target-y += gthread
target-y += size

CC := gcc

CFLAGS :=
LDFLAGS :=

GLIB_VERSION := glib-2.0
GLIB_LIBS := $(shell pkg-config --libs ${GLIB_VERSION})
GLIB_CFLAGS := $(shell pkg-config --cflags ${GLIB_VERSION})

$(info GLIB_CFLAGS=$(GLIB_CFLAGS))
$(info GLIB_LIBS=$(GLIB_LIBS))

CFLAGS += $(GLIB_CFLAGS)
CFLAGS += $(GLIB_LIBS)

LDFLAGS += $(GLIB_LIBS)

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
  ifneq (${CC_M32},1)
    $(error ${CC} not support -m32)
  endif
endif

include ../../../template/main.mk

gthread: gthread.o
size: size.o
