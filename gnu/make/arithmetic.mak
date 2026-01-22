# SPDX-License-Identifier: GPL-3.0

N1 := $(shell echo "1 + 2" | bc)
N2 := $(shell expr 1 + 2)

$(info N1 = ${N1})
$(info N2 = ${N2})

ifneq (${N1},3)
  $(error N1 != ${N1})
endif

.PHONY: build
build:
