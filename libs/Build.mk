# SPDX-License-Identifier: GPL-3.0
include kconfig.mk

target-y += byteswap
target-y += endian
target-y += file
target-y += fd
target-y += gotoxy goprint
target-y += log
target-y += memshow
target-y += mac
target-y += progress
target-y += str
target-y += ipaddr

target-libso-y += libtest-linux-c.so.0.1
target-liba-y += libtest-linux-c.a

target-test-y += test1

objs-dynamic += ${OUTPUT}byteswap.so.o
objs-dynamic += ${OUTPUT}endian.so.o
objs-dynamic += ${OUTPUT}fd.so.o
objs-dynamic += ${OUTPUT}file.so.o
objs-dynamic += ${OUTPUT}log.so.o
objs-dynamic += ${OUTPUT}ipaddr.so.o
objs-dynamic += ${OUTPUT}readline.so.o
objs-dynamic += ${OUTPUT}mac.so.o
objs-dynamic += ${OUTPUT}memshow.so.o
objs-dynamic += ${OUTPUT}progress.so.o
objs-dynamic += ${OUTPUT}str.so.o
objs-static := $(patsubst %.so.o,%.a.o,${objs-dynamic})

libtest-linux-c.a-objs := ${objs-static}
libtest-linux-c.so.0.1-objs := ${objs-dynamic}

CFLAGS += -DTEST_MAIN=1
ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

ifdef LINK_LIB
  CFLAGS += -ltest-linux-c
  LDFLAGS += libtest-linux-c.so.0.1
endif
