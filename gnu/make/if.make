# SPDX-License-Identifier: GPL-3.0

VAR1 := a.c
FLAG1 := $(if $(filter %.c,${VAR1}),YES)

$(info VAR1 = $(VAR1))
$(info FLAG1 = ${FLAG1})

.PHONY: build
build:
