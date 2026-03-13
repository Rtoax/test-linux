# SPDX-License-Identifier: GPL-3.0
include helpers.mk

target-y := dl_iterate_phdr
target-y += dl_iterate_phdr-pie
target-y += has_shared_object

dl_iterate_phdr-objs := ${PROC_HELPERS}
dl_iterate_phdr-pie-objs := ${PROC_HELPERS}

CFLAGS_dl_iterate_phdr := -no-pie
LDFLAGS_dl_iterate_phdr := -no-pie
CFLAGS_dl_iterate_phdr-pie := -fpie
LDFLAGS_dl_iterate_phdr-pie := -pie
