# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_C_MK
_TARGET_C_MK = 1

CC ?= gcc
OBJCOPY ?= objcopy

include cflags.mk

${OUTPUT}%.o: %.c | ${OUTPUT}
	$(call log_obj,CC,$(@))
	${Q}$(if ${CC_${*}},${CC_${*}},${CC}) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.o.bin: ${OUTPUT}%.o
	$(call log_obj,OBJCOPY BIN,$(@))
	${Q}$(OBJCOPY) -O binary $(<) $(@)

# Compile .c to .<N>.o, this use to compile single source code to more than one
# object file.
define c_obj_x
$${OUTPUT}%.${1}.o: %.c | $${OUTPUT}
	$$(call log_obj,CC.${1},$$(@))
	$${Q}$$(if $${CC_$${*}},$${CC_$${*}},$${CC}) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CFLAGS) $$(CFLAGS_$$(*).${1})
endef
$(foreach i, ${SRC_SFX_LIST}, $(eval $(call c_obj_x,${i})))

${OUTPUT}%.E.c: %.c | ${OUTPUT}
	$(call log_obj,CC E,$(@))
	${Q}$(if ${CC_${*}},${CC_${*}},${CC}) -E -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	$(call log_obj,CC S,$(@))
	${Q}$(if ${CC_${*}},${CC_${*}},${CC}) -S -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

$(target-y): %:
	$(call log_tgt,LD,$(@))
	${Q}$(if ${CC_${*}},${CC_${*}},${CC}) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

$(foreach t, ${target-y}, \
  $(eval ${t}-objs := $(call append_output_prefix,${${t}-objs})) \
  $(if ${DEBUG},$(info ${t}-objs = ${${t}-objs})) \
  $(if $(shell test -f ${t}.c && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
  $(if ${${t}-deps}, $(eval ${t}: ${${t}-deps})) \
)

$(foreach t, ${target-y}, \
  $(if $(shell test -f ${OUTPUT}${t}.o.d && echo yes), \
    $(if ${DEBUG}, $(info Found ${t}'s dep ${OUTPUT}${t}.o.d)) \
    $(foreach tobj, ${${t}-objs}, \
      $(if $(shell test -f ${tobj}.d && echo yes), \
        $(if ${DEBUG}, $(info Found ${t}'s obj dep ${tobj}.d)) \
        $(eval include ${tobj}.d) \
      ) \
    ) \
    $(eval include ${OUTPUT}${t}.o.d), \
    $(if ${DEBUG}, $(info Not found ${OUTPUT}${t}.o.d)) \
  ) \
)

endif
