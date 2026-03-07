# SPDX-License-Identifier: GPL-3.0
#
# $(if condition,then-part,else-part)
#
VAR1 := a.c
FLAG1 := $(if $(filter %.c,${VAR1}),YES)

$(if ${DEBUG},$(info define DEBUG),$(info not define DEBUG))

$(info VAR1 = $(VAR1))
$(info FLAG1 = ${FLAG1})

.PHONY: build
build:
