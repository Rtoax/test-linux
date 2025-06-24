# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += fork vfork fork-share
TARGETS += fork-ENOMEM fork-ENOMEM-2
TARGETS += fork_twice

CFLAGS := -D__USE_GNU
CFLAGS += -pthread

CFLAGS_vfork := -DVFORK=1

include ../../../../template/main.mk

fork_helpers.o: fork_helpers.h

fork: fork.o
vfork: vfork.o
fork_twice: fork_twice.o
fork-share: fork-share.o
fork-ENOMEM: fork-ENOMEM.o fork_helpers.o
fork-ENOMEM-2: fork-ENOMEM-2.o fork_helpers.o
