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

prog-y := environ.sh
prog-y += numa_maps.sh
prog-y += stat.sh

CFLAGS_pagemap := -DHAVE_MAIN=1
LDFLAGS_pagemap += -lnuma
