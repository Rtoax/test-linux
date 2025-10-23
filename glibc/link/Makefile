# SPDX-License-Identifier: GPL-3.0
__USE_PROC_HELPERS__ := 1

target-y := dl_iterate_phdr
target-y += dl_iterate_phdr-pie
target-y += has_shared_object

CFLAGS_dl_iterate_phdr := -no-pie
LDFLAGS_dl_iterate_phdr := -no-pie
CFLAGS_dl_iterate_phdr-pie := -fpie
LDFLAGS_dl_iterate_phdr-pie := -pie

include ../../template/main.mk

dl_iterate_phdr: dl_iterate_phdr.o ${PROC_HELPERS}
dl_iterate_phdr-pie: dl_iterate_phdr-pie.o ${PROC_HELPERS}
has_shared_object: has_shared_object.o
