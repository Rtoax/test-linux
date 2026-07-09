# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - add_target_objects()
# - add_library_objects()
#
ifndef _BITS_TARGETS_MK
_BITS_TARGETS_MK = 1

# Add target objects depends
# need called after target_objects_append_output_prefix()
#
# $1: source file extension like .cpp in a.cpp
# $2: object file extension like .o for .c, .cpp.o for .cpp
# $3: targets
# $4: default depends, could be empty.
#     for examples: HELPERS
define add_target_objects
$(foreach tgt, ${3}, \
  $(if ${DEBUG},$(info ${tgt}-objs = ${${tgt}-objs})) \
  $(if $(shell test -f ${tgt}${1} && echo yes), \
    $(if ${DEBUG},$(info ${tgt}: ${OUTPUT}${tgt}${2} ${${tgt}-objs} ${4})) \
    $(eval ${tgt}: ${OUTPUT}${tgt}${2} $${${tgt}-objs} ${4}), \
    $(if ${DEBUG},$(info ${tgt}: ${${tgt}-objs} ${4})) \
    $(eval ${tgt}: $${${tgt}-objs} ${4}) \
  ) \
)
endef

# Add library objects depends
# $1: targets
# $2: default depends, could be empty.
#     for examples: HELPERS
define add_library_objects
$(call add_target_objects,___shoud_not_exist___,,$1,$2)
endef

endif # end of _BITS_TARGETS_MK
