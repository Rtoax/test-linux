# SPDX-License-Identifier: GPL-3.0

OUTPUT := .output0/
OUTPUT += .output1/
OUTPUT += .output2/
OUTPUT += .output3/a
OUTPUT += .output3/b

$(info OUTPUT = ${OUTPUT})

ifneq ($(filter %/,$(OUTPUT)),)
  $(info end with /)
endif

$(info a = $(filter a,a b c))

$(info filter-out $${OUTPUT} = $(filter-out .output2/,${OUTPUT}))
$(info filter-out $${OUTPUT} = $(filter-out .output3/%,${OUTPUT}))
$(info filter-out $${OUTPUT} = $(filter-out .output2% .output3%,${OUTPUT}))

objs += .output/a.o b.o .output/c.o /d.o
$(info objs = ${objs})
$(info $(addprefix .output/,$(filter-out .output/%,$(objs))) $(filter .output/%,$(objs)))
$(info $(foreach f,$(objs),$(if $(findstring .output/,$(f)),$(f),.output/$(f))))
$(info $(foreach f,$(objs),$(if $(filter .output/% /%,$(f)),$(f),.output/$(f))))

.PHONY: build
build:
