# SPDX-License-Identifier: GPL-3.0
TARGETS := lstat
TARGETS += stat
TARGETS += statx
TARGETS += fstat
TARGETS += listdir
TARGETS += chmod
TARGETS += fchmod
TARGETS += mkdir
TARGETS += mknod
TARGETS += st_mode
TARGETS += fstatat
TARGETS += utimensat
TARGETS += futimens
TARGETS += ustat

CFLAGS :=
CFLAGS += -pthread

CFLAGS_futimens := -DFUTIMENS=1

include ../../../template/main.mk

stat_helpers.o: stat_helpers.h

stat: stat.o stat_helpers.o
statx: statx.o stat_helpers.o
fstat: fstat.o stat_helpers.o proc_helpers.o
lstat: lstat.o stat_helpers.o
listdir: listdir.o
chmod: chmod.o
fchmod: fchmod.o
mkdir: mkdir.o
mknod: mknod.o
fstatat: fstatat.o stat_helpers.o proc_helpers.o
st_mode: st_mode.o stat_helpers.o
utimensat: utimensat.o
futimens: futimens.o
ustat: ustat.o stat_helpers.o
