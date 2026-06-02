# SPDX-License-Identifier: GPL-3.0
target-y += mice mouse0
target-y += event0 keyboard keyboard2

CFLAGS_mouse0 := -DDEV_INPUT_MOUSE0=1
