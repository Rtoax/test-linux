# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += if_indextoname
TARGETS += if_nametoindex
TARGETS += if_nameindex

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=

include ../../../template/main.mk

if_indextoname: if_indextoname.o
if_nametoindex: if_nametoindex.o
if_nameindex: if_nameindex.o
