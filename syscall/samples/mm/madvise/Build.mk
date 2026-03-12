# SPDX-License-Identifier: GPL-3.0
target-y += madvise-MADV_MERGEABLE
target-y += madvise-MADV_HUGEPAGE

CFLAGS += -pthread
