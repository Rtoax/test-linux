# SPDX-License-Identifier: GPL-3.0

N1 := $(shell echo "1 + 2" | bc)
N2 := $(shell expr 1 + 2)
N3 := $(shell expr $$(expr 1 + 5) / 3)

$(info N1 = ${N1})
$(info N2 = ${N2})
$(info N3 = ${N3})

ifneq (${N1},3)
  $(error N1 != 3)
endif
ifneq (${N3},2)
  $(error N3 != 2)
endif

.PHONY: build
build:
