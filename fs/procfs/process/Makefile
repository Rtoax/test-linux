# SPDX-License-Identifier: GPL-3.0
targets :=
targets += cmdline
targets += environ
targets += exe
targets += loginuid
targets += pagemap
targets += mem
targets += maps
targets += stat

CFLAGS_pagemap := -DHAVE_MAIN=1
LDFLAGS_pagemap += -lnuma

include ../../../template/main.mk

cmdline: cmdline.o
environ: environ.o
exe: exe.o
loginuid: loginuid.o
pagemap: pagemap.o
mem: mem.o
maps: maps.o
stat: stat.o
