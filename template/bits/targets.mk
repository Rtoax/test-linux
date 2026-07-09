# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - add_target_objects()
# - add_target_depends()
# - add_library_objects()
#
ifndef _BITS_TARGETS_MK
_BITS_TARGETS_MK = 1

include output.mk

# Add target objects depends
# need called after target_objects_append_output_prefix()
#
# $1: source file extension like .cpp for a.cpp, .c for a.c
# $2: object file extension like .o for .c, .cpp.o for .cpp
# $3: target list
# $4: default depends, could be empty.
#     for examples: HELPERS
define add_target_objects
$(foreach tgt, ${3}, \
  $(if ${DEBUG},$(info ${tgt}-objs = ${${tgt}-objs})) \
  $(if ${1}, \
    $(if $(shell test -f ${tgt}${1} && echo yes), \
      $(eval ${tgt}-objs += $(call append_output_prefix,${tgt}${2})) \
    ) \
    $(if $(shell test -f ${tgt}${1} && echo yes), \
      $(if ${DEBUG},$(info ${tgt}: ${OUTPUT}${tgt}${2} ${${tgt}-objs} ${4})) \
      $(eval ${tgt}: ${OUTPUT}${tgt}${2} $${${tgt}-objs} ${4}), \
      $(if ${DEBUG},$(info ${tgt}: ${${tgt}-objs} ${4})) \
      $(eval ${tgt}: $${${tgt}-objs} ${4}) \
    ) \
  ) \
)
endef

# Add target depends
#
# $1: target list
define add_target_depends
$(foreach tgt, ${1}, \
  $(if ${DEBUG}, $(info ${tgt}: ${${tgt}-deps})) \
  $(if ${${tgt}-deps}, $(eval ${tgt}: ${${tgt}-deps})) \
  $(foreach obj, ${${tgt}-objs}, \
    $(eval _obj := $(call strip_output_prefix,${obj})) \
    $(if ${${_obj}-deps}, \
      $(eval ${obj}: ${${_obj}-deps})\
      $(if ${DEBUG}, $(info ${obj}: ${${_obj}-deps})) \
    ) \
  ) \
)
endef

# Add library objects depends
# $1: targets
# $2: default depends, could be empty.
#     for examples: HELPERS
define add_library_objects
$(call add_target_objects,,,$1,$2)
endef

endif # end of _BITS_TARGETS_MK
