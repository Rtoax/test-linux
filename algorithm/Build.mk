# SPDX-License-Identifier: GPL-3.0
subdir-y += bitmap
subdir-y += bitmask
subdir-y += bitops
subdir-y += bits
subdir-y += fft
subdir-y += hash
subdir-y += hashmap
subdir-y += hweight
subdir-y += ida
subdir-y += list
subdir-y += linklist
subdir-y += rbtree
subdir-y += md5
subdir-y += math
subdir-y += string
subdir-y += sort
subdir-y += search

target-y += pi

CFLAGS += -I../macro/
