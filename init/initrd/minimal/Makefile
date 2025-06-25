# SPDX-License-Identifier: GPL-3.0
TARGETS := fakeinit
TARGETS_POST := initrd.img

CFLAGS := -static

include ../../../template/main.mk

initrd.img:
	${Q}./build-initrd.sh

fakeinit: fakeinit.o
