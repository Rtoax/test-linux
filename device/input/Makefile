# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += mice mouse0
target-y += event0 keyboard

CFLAGS_mouse0 := -DDEV_INPUT_MOUSE0=1

include ../../template/main.mk

mice: mice.o
mouse0: mouse0.o
event0: event0.o
keyboard: keyboard.o
