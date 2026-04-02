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
target-y += ksym_examples
target-y += proc_examples

libproc-helpers := libproc_helpers.so.0.1.0

target-liba-y += libtest-linux-c.a
target-liba-y += libproc_helpers.a
target-liba-y += libksym_helpers.a

target-libso-y += libtest-linux-c.so.0.1
target-libso-y += ${libproc-helpers}
target-libso-y += libksym_helpers.so

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
objs-dynamic += ${OUTPUT}syscall_helpers.so.o
objs-static := $(patsubst %.so.o,%.a.o,${objs-dynamic})

libtest-linux-c.a-objs := ${objs-static}
libtest-linux-c.so.0.1-objs := ${objs-dynamic}
libksym_helpers.a-objs := ${OUTPUT}ksym_helpers.a.o
libksym_helpers.so-objs := ${OUTPUT}ksym_helpers.so.o
libproc_helpers.a-objs := ${OUTPUT}proc_helpers.a.o
${libproc-helpers}-objs := ${OUTPUT}proc_helpers.so.o

ksym_examples-objs := ${OUTPUT}ksym_helpers.o
proc_examples-objs := ${libproc-helpers}

CFLAGS += -DTEST_MAIN=1
ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

ifdef LINK_LIB
  CFLAGS += -ltest-linux-c
  LDFLAGS += libtest-linux-c.so.0.1
endif

LDFLAGS_SO_${libproc-helpers} := -Wl,--version-script=proc_helpers.map
