# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
include kconfig.mk

subdir-y := readline

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

CFLAGS += -DTEST_MAIN=1
ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

ifdef LINK_LIB
  CFLAGS += -ltest-linux-c
  LDFLAGS += libtest-linux-c.so.0.1
endif

include main.mk

test1:
	$(call log_exe,TEST,,$(@))
	${Q}LD_LIBRARY_PATH=$(shell pwd) ./byteswap
	${Q}clear
	${Q}./gotoxy
	${Q}clear
	${Q}./file.sh test

%.so.o: %.h

byteswap: ${OUTPUT}byteswap.o
byteswap.o: byteswap.h
endian: ${OUTPUT}endian.o
endian.o: endian.h
gotoxy: ${OUTPUT}gotoxy.o
goprint: ${OUTPUT}goprint.o
file: ${OUTPUT}file.o
file.o: file.h
fd: ${OUTPUT}fd.o
fd.o: fd.h
log: ${OUTPUT}log.o
log.o: log.h
memshow: ${OUTPUT}memshow.o
mac: ${OUTPUT}mac.o
mac.o: mac.h
progress: ${OUTPUT}progress.o
progress.o: progress.h
str: ${OUTPUT}str.o
ipaddr: ${OUTPUT}ipaddr.o
ipaddr.o: ipaddr.h

objs-dynamic := ${OUTPUT}ipaddr.so.o
objs-dynamic += ${OUTPUT}readline.so.o
objs-dynamic += ${OUTPUT}memshow.so.o
objs-dynamic += ${OUTPUT}str.so.o
objs-static := $(patsubst %.so.o,%.a.o,${objs-dynamic})

libtest-linux-c.so.0.1: ${objs-dynamic}
libtest-linux-c.a: ${objs-static}
