# SPDX-License-Identifier: GPL-3.0
target-y := fakeinit
target-post-y := initrd.img

CFLAGS := -static

include ../../../template/main.mk

initrd.img:
	${Q}./build-initrd.sh

fakeinit: fakeinit.o
