# SPDX-License-Identifier: GPL-3.0
targets := dl_iterate_phdr
targets += dl_iterate_phdr-pie
targets += has_shared_object

targets-liba := proc_helpers.a

CFLAGS_dl_iterate_phdr := -no-pie
LDFLAGS_dl_iterate_phdr := -no-pie
CFLAGS_dl_iterate_phdr-pie := -fpie
LDFLAGS_dl_iterate_phdr-pie := -pie

include ../../template/main.mk

proc_helpers.a.o: proc_helpers.h
proc_helpers.a: proc_helpers.a.o

dl_iterate_phdr: dl_iterate_phdr.o proc_helpers.a
dl_iterate_phdr-pie: dl_iterate_phdr-pie.o proc_helpers.a
has_shared_object: has_shared_object.o
