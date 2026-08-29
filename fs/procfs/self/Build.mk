# SPDX-License-Identifier: GPL-3.0
include helpers.mk

subdir-y += root

target-y += auxv
target-y += cmdline
target-y += environ
target-y += exe
target-y += loginuid
target-y += pagemap
target-y += mem
target-y += maps
target-y += self
target-y += stat
target-y += statm
target-y += status

self-objs := ${PROC_HELPERS}

prog-y += environ.sh
prog-y += numa_maps.sh
prog-y += ns.sh
prog-y += stat.sh

CFLAGS_pagemap := -DHAVE_MAIN=1
LDFLAGS_pagemap += -lnuma
