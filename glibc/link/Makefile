# SPDX-License-Identifier: GPL-3.0
CC := gcc
LIBPROCFS_DIR := ../../fs/procfs/

TARGETS := dl_iterate_phdr
TARGETS += dl_iterate_phdr-pie
TARGETS += has_shared_object

CFLAGS :=
CFLAGS += -I${LIBPROCFS_DIR}

LDFLAGS :=

CFLAGS_dl_iterate_phdr := -no-pie
CFLAGS_dl_iterate_phdr-pie := -fpie
LDFLAGS_dl_iterate_phdr-pie := -pie

include ../../template/main.mk

dl_iterate_phdr: dl_iterate_phdr.o libtest-linux-procfs.a
dl_iterate_phdr-pie: dl_iterate_phdr-pie.o libtest-linux-procfs.a
has_shared_object: has_shared_object.o

include ${LIBPROCFS_DIR}/procfs-lib-target.mk
