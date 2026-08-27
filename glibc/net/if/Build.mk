# SPDX-License-Identifier: GPL-3.0
include net/if.mk

target-y += if_indextoname
target-y += if_nametoindex
target-y += if_nameindex

prog-y += ${target-y}

PROG_ARGS_if_nametoindex := ${IF_NAMES}
