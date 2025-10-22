# SPDX-License-Identifier: GPL-3.0

subdir-y := bitmask
subdir-y += bitops
subdir-y += fft
subdir-y += hashmap
subdir-y += list
subdir-y += linklist
subdir-y += rbtree
subdir-y += md5
subdir-y += math
subdir-y += string
subdir-y += sort
subdir-y += search

target-y :=
target-y += pi

CFLAGS :=
CFLAGS += -I../macro/

include ../template/main.mk

pi: pi.o
