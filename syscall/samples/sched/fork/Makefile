# SPDX-License-Identifier: GPL-3.0
target-y += fork vfork fork-share
target-y += fork-ENOMEM fork-ENOMEM-2
target-y += fork_twice

fork-ENOMEM-objs := fork_helpers.o
fork-ENOMEM-2-objs := fork_helpers.o

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

CFLAGS_vfork := -DVFORK=1

include main.mk
