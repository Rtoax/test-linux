# SPDX-License-Identifier: GPL-3.0

ARRAY := 1
ARRAY += 2
ARRAY += 3

$(info word2 = $(word 2,${ARRAY}))
$(info word3 = $(word 3,${ARRAY}))

.PHONY: build
build:
