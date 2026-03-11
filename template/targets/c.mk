# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_C_MK
_TARGET_C_MK = 1

CC ?= gcc

include cflags.mk

${OUTPUT}%.o: %.c | ${OUTPUT}
	$(call log_obj,CC,$(@))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.E.c: %.c | ${OUTPUT}
	$(call log_obj,CC E,$(@))
	${Q}$(CC) -E -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	$(call log_obj,CC S,$(@))
	${Q}$(CC) -S -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

$(target-y): %:
	$(call log_tgt,LD,$(@))
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

$(foreach t, ${target-y}, \
  $(if $(shell test -f ${t}.c && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
)

# TODO: need include ${t}-objs .d file
$(foreach t, ${target-y}, \
  $(if $(shell test -f ${OUTPUT}${t}.o.d && echo yes), \
    $(if ${DEBUG}, $(info Found ${OUTPUT}${t}.o.d)) \
    $(eval include ${OUTPUT}${t}.o.d), \
    $(if ${DEBUG}, $(info Not found ${OUTPUT}${t}.o.d)) \
  ) \
)

endif
