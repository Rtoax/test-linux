# SPDX-License-Identifier: GPL-3.0
#
# $(or condition-part,else-part)
#
VAR1 := a.c
FLAG1 := $(or $(filter %.c,${VAR1}),YES)

FLAG2 := $(or ${DEBUG},"Not define DEBUG")

$(info VAR1 = $(VAR1))
$(info FLAG1 = ${FLAG1})
$(info FLAG2 = ${FLAG2})

.PHONY: build
build:
