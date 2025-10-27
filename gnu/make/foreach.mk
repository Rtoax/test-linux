# SPDX-License-Identifier: GPL-3.0
#
# $(foreach var, list, text)
#

VAR1 := a.c b.c c.c
VAR2 := $(VAR1:.c=.o)

.PHONY: build
build: ${VAR2}
	@echo $(foreach var,${VAR1},"$(var) ")
	@echo $(foreach var,${VAR2},"$(var) ")

# Create object targets
$(foreach var, ${VAR2},	\
$(eval ${var}:	;\
	@echo ${var})	\
)
