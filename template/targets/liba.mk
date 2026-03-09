# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_LIBA_MK
_TARGET_LIBA_MK = 1

include cflags.mk

CC ?= gcc
Q ?= @

CFLAGS_A += -fPIC

ifdef DEBUG
  $(info CFLAGS_A = ${CFLAGS_A})
endif

$(foreach lib, ${target-liba-y}, $(eval ${lib}: $${${lib}-objs}))

${OUTPUT}%.a.o: %.c | ${OUTPUT}
	$(call log_obj,CC A.o,$(@))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*))

$(target-liba-y): %:
	$(call log_tgt,AR,$(@))
	${Q}ar rcs $(@) $(^)

endif
