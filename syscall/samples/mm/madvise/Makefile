# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += madvise-MADV_MERGEABLE
TARGETS += madvise-MADV_HUGEPAGE

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread

include ../../../../template/main.mk

madvise-MADV_MERGEABLE: madvise-MADV_MERGEABLE.o
madvise-MADV_HUGEPAGE: madvise-MADV_HUGEPAGE.o
