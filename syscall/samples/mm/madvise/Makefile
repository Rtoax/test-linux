# SPDX-License-Identifier: GPL-3.0
targets :=
targets += madvise-MADV_MERGEABLE
targets += madvise-MADV_HUGEPAGE

CFLAGS :=
CFLAGS += -pthread

include ../../../../template/main.mk

madvise-MADV_MERGEABLE: madvise-MADV_MERGEABLE.o
madvise-MADV_HUGEPAGE: madvise-MADV_HUGEPAGE.o
