# SPDX-License-Identifier: GPL-3.0
target-y := nostdlib
target-y += btf_ids

LDFLAGS_nostdlib := -nostdlib

include main.mk

btf_ids: btf_ids.o
nostdlib: nostdlib.o
