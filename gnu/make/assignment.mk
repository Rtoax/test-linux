# SPDX-License-Identifier: GPL-3.0

BPFTOOL := bpftool
BPFTOOL ?= /path/to/bpftool
# Print := one
$(info BPFTOOL = ${BPFTOOL})

.PHONY: build
build:
