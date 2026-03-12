# SPDX-License-Identifier: GPL-3.0
include compiler.mk
target-y := main
target-y += main-pg
# FIXME: aarch64 seems like don't support -mfentry
target-${feature-mfentry} += main-pg-fentry

main-objs := foo.o
main-pg-objs := foo-pg.o
main-pg-fentry-objs := foo-pg-fentry.o

CFLAGS_main-pg := -pg
CFLAGS_main-pg-fentry := -pg -mfentry

CFLAGS_foo-pg := -pg
CFLAGS_foo-pg-fentry := -pg -mfentry
