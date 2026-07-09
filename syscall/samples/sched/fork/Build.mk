# SPDX-License-Identifier: GPL-3.0
include helpers.mk

target-y += fork
target-${IS_X86_64} += sys_fork
target-y += vfork
target-${IS_X86_64} += sys_vfork
target-y += fork-share
target-y += fork-ENOMEM fork-ENOMEM-2
target-y += fork_twice

sys_fork-objs += fork.1.o ${SCHED_HELPERS}
sys_vfork-objs += vfork.1.o ${SCHED_HELPERS}
fork-ENOMEM-objs := helpers.o
fork-ENOMEM-2-objs := helpers.o

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

CFLAGS_fork.1 := -DSYSCALL=1
CFLAGS_vfork := -DVFORK=1
CFLAGS_vfork.1 := -DSYSCALL=1 -DVFORK=1
