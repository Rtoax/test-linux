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

# append ${OUTPUT} for each object
$(foreach a, ${target-liba-y} ${target-liba-cpp-y}, \
  $(eval ${a}-objs := $(call append_output_prefix,${${a}-objs})) \
  $(if ${DEBUG},$(info ${a}-objs = ${${a}-objs})) \
)

$(foreach lib, ${target-liba-y}, $(eval ${lib}: $${${lib}-objs}))

${OUTPUT}%.a.o: %.c | ${OUTPUT}
	$(call log_obj,CC A.o,$(@))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*))

$(target-liba-y): %:
	$(call log_tgt,AR,$(@))
	${Q}ar rcs $(@) $(^)

$(foreach a, ${target-liba-y}, \
  $(foreach obj, ${${a}-objs}, \
    $(if $(shell test -f ${obj}.d && echo yes), \
      $(if ${DEBUG}, $(info Include ${obj}.d)) \
      $(eval include ${obj}.d), \
      $(if ${DEBUG}, $(info Not found ${obj}.d)) \
    ) \
  ) \
  $(if ${${a}-deps}, $(eval ${a}: ${${a}-deps}) \
    $(if ${DEBUG}, $(info ${a}: ${${a}-deps}))) \
)

endif
