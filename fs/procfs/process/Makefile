# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += cmdline
target-y += environ
target-y += exe
target-y += loginuid
target-y += pagemap
target-y += mem
target-y += maps
target-y += stat
target-y += statm
target-y += status

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
statm: statm.o
status: status.o
