# SPDX-License-Identifier: GPL-3.0
$(foreach btf, $(shell ls /sys/kernel/btf/), $(eval target-btf-y += ${btf}.h))
include main.mk
