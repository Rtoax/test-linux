# SPDX-License-Identifier: GPL-3.0

$(info 1 + 2 = $(shell expr 1 + 2))
$(info 1 << 2 = $(shell echo "$$(( (1 << 2) + (2 << 1) ))" ))

.PHONY: build
build:
