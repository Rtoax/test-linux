# SPDX-License-Identifier: GPL-3.0
include ../kconfig.mk

sub-dir := readline

targets-libso :=
targets-liba :=
targets :=
CFLAGS :=
targets-test :=

targets += byteswap
targets += endian
targets += file
targets += fd
targets += gotoxy goprint
targets += log
targets += memshow
targets += mac
targets += progress
targets += str
targets += ipaddr

LIB_OBJS := ipaddr.so.o readline.so.o
LIB_OBJS_A := ipaddr.a.o readline.a.o

targets-libso += libtest-linux-c.so.0.1
targets-liba += libtest-linux-c.a

targets-test += test1

CFLAGS += -DTEST=1
ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

ifdef LINK_LIB
  CFLAGS += -ltest-linux-c
  LDFLAGS += libtest-linux-c.so.0.1
endif

include ../template/main.mk

test1:
	$(call log_tgt_exe,TEST,,$(@))
	${Q}LD_LIBRARY_PATH=$(shell pwd) ./byteswap
	${Q}clear
	${Q}./gotoxy
	${Q}clear
	${Q}./file.sh test

%.so.o: %.h

byteswap: byteswap.o
byteswap.o: byteswap.h
endian: endian.o
endian.o: endian.h
gotoxy: gotoxy.o
goprint: goprint.o
file: file.o
file.o: file.h
fd: fd.o
fd.o: fd.h
log: log.o
log.o: log.h
memshow: memshow.o
mac: mac.o
mac.o: mac.h
progress: progress.o
progress.o: progress.h
str: str.o
ipaddr: ipaddr.o
ipaddr.o: ipaddr.h

libtest-linux-c.so.0.1: ${LIB_OBJS}
libtest-linux-c.a: ${LIB_OBJS_A}
