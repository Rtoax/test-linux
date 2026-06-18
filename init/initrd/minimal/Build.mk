# SPDX-License-Identifier: GPL-3.0
target-y := fakeinit
post-y := initrd.img

LDFLAGS := -static
