# SPDX-License-Identifier: GPL-3.0
#
# $(foreach var, list, text)
#

VAR1 := a.c b.c c.c
VAR2 := $(VAR1:.c=.o)
VAR3 := $(VAR1:.c=.o.x)

.PHONY: build
build: ${VAR2} ${VAR3}
	@echo $(foreach var,${VAR1},"$(var) ")
	@echo $(foreach var,${VAR2},"$(var) ")
	@echo $(foreach var,${VAR3},"$(var) ")

# Create object targets
$(foreach var, ${VAR2},	\
$(eval ${var}:	;\
	@echo ${var})	\
)

$(foreach var, ${VAR3},	\
$(if $(filter %.o.x,${var}),\
	$(eval ${var}:	;\
		@echo ${var})	\
)	\
)
