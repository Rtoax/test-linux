# SPDX-License-Identifier: GPL-3.0
target-y += mount
target-prog-y += mount.sh

CFLAGS_mount := -DTEST_MAIN=1
