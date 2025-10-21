# SPDX-License-Identifier: GPL-3.0
include ../../compiler/compiler.mk
target-y := main
target-y += main-pg
# FIXME: aarch64 seems like don't support -mfentry
ifeq ($(CC_-mfentry),1)
  target-y += main-pg-fentry
endif

CFLAGS_main-pg := -pg
CFLAGS_main-pg-fentry := -pg -mfentry

CFLAGS_foo-pg := -pg
CFLAGS_foo-pg-fentry := -pg -mfentry

include ../../template/main.mk

main: main.o foo.o
main-pg: main-pg.o foo-pg.o
main-pg-fentry: main-pg-fentry.o foo-pg-fentry.o
