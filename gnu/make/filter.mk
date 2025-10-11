# SPDX-License-Identifier: GPL-3.0

OUTPUT := .output/
OUTPUT += .output1/
OUTPUT += .output2/

$(info OUTPUT = ${OUTPUT})

ifneq ($(filter %/,$(OUTPUT)),)
  $(info end with /)
endif

$(info filter-out $${OUTPUT} = $(filter-out .output2/,${OUTPUT}))

.PHONY: build
build:
