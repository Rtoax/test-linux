# SPDX-License-Identifier: GPL-3.0
target-y += auxv
target-y += cmdline
target-y += environ
target-y += exe
target-y += loginuid
target-y += pagemap
target-y += mem
target-y += maps
target-y += stat
target-y += statm
target-y += status

target-shell-y := environ.sh
target-shell-y += numa_maps.sh
target-shell-y += stat.sh

CFLAGS_pagemap := -DHAVE_MAIN=1
LDFLAGS_pagemap += -lnuma

include main.mk
