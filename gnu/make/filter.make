# SPDX-License-Identifier: GPL-3.0

OUTPUT := .output/
OUTPUT += .output1/
OUTPUT += .output2/
OUTPUT += .output3/a
OUTPUT += .output3/b

$(info OUTPUT = ${OUTPUT})

ifneq ($(filter %/,$(OUTPUT)),)
  $(info end with /)
endif

$(info $(filter a,a b c))

$(info filter-out $${OUTPUT} = $(filter-out .output2/,${OUTPUT}))
$(info filter-out $${OUTPUT} = $(filter-out .output3/%,${OUTPUT}))

.PHONY: build
build:
