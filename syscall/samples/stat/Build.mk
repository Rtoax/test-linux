# SPDX-License-Identifier: GPL-3.0
__USE_PROC_HELPERS__ = y
include helpers.mk

target-y := lstat
target-y += stat
target-y += statx
target-y += fstat
target-y += listdir
target-y += chmod
target-y += fchmod
target-y += mkdir
target-y += mknod
target-y += st_mode
target-y += fstatat
target-y += utimensat
target-y += futimens
target-y += ustat

stat-objs := stat_helpers.o
statx-objs := stat_helpers.o
fstat-objs := stat_helpers.o ${PROC_HELPERS}
lstat-objs := stat_helpers.o
fstatat-objs := stat_helpers.o ${PROC_HELPERS}
st_mode-objs := stat_helpers.o
ustat-objs := stat_helpers.o

CFLAGS += -pthread
CFLAGS_futimens := -DFUTIMENS=1
