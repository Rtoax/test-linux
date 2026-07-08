# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_LIBA_MK
_TARGET_LIBA_MK = 1

include cflags.mk

CC ?= gcc

CFLAGS_A += -fPIC

ifdef DEBUG
  $(info CFLAGS_A = ${CFLAGS_A})
endif

# append ${OUTPUT} for each library objects, for example:
#
#   target-liba-y := libx.a
#   libx.a-objs := x.a.o
#
# Then, add ${OUTPUT} prefix:
#
#   libx.a-objs := ${OUTPUT}x.a.o
#
$(foreach a, ${target-liba-y} ${target-liba-cpp-y}, \
  $(eval ${a}-objs := $(call append_output_prefix,${${a}-objs})) \
  $(if ${DEBUG},$(info liba: ${a}-objs = ${${a}-objs})) \
)

$(foreach lib, ${target-liba-y}, $(eval ${lib}: $${${lib}-objs}))

${OUTPUT}%.a.o: %.c | ${OUTPUT}
	$(call log_obj,${CC} A.o,$(@))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*))

$(target-liba-y): %:
	$(call log_tgt,AR,$(@))
	${Q}ar rcs $(@) $(^)

# Auto add library object.d and object's depends, for example:
#
#   target-liba-y := libx.a
#   libx.a-deps := x.h
#   libx.a-objs := ${OUTPUT}x.a.o # add ${OUTPUT} above
#   x.a.o-deps := x.h y.h z.h
#
# Then:
#
#   include ${OUTPUT}x.a.o.d
#   ${OUTPUT}x.a.o: x.h y.h z.h
#   libx.a: x.h
#
$(foreach a, ${target-liba-y}, \
  $(foreach obj, ${${a}-objs}, \
    $(if $(shell test -f ${obj}.d && echo yes), \
      $(if ${DEBUG}, $(info Include ${obj}.d)) \
      $(eval include ${obj}.d), \
      $(if ${DEBUG}, $(info Not found ${obj}.d)) \
    ) \
    $(eval _obj := $(call strip_output_prefix,${obj})) \
    $(if ${${_obj}-deps}, $(eval ${obj}: ${${_obj}-deps})\
      $(if ${DEBUG}, $(info ${obj}: ${${_obj}-deps})) \
    ) \
  ) \
  $(if ${${a}-deps}, $(eval ${a}: ${${a}-deps}) \
    $(if ${DEBUG}, $(info ${a}: ${${a}-deps}))) \
)

endif
