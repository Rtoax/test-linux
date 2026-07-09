# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - append_output_prefix()
# - target_objects_append_output_prefix()
# - strip_output_prefix()
#
ifndef _OUTPUT_MK
_OUTPUT_MK = 1

OUTPUT := .output/

# $1: input words, like: a b c /d
# output: ${OUTPUT}a ${OUTPUT}b ${OUTPUT}c /d
define append_output_prefix
$(foreach f,${1},$(if $(filter ${OUTPUT}% /%,$(f)),$(f),${OUTPUT}$(f)))
endef

# Append ${OUTPUT} for each target's objects
#
# For example:
#
#   targets := x
#   x-objs := x1.o x2.o
#
# Then, add ${OUTPUT} prefix:
#
#   x-objs := ${OUTPUT}x1.o ${OUTPUT}x2.o
#
# $1: target list
define target_objects_append_output_prefix
$(foreach tgt, ${1}, \
  $(eval ${tgt}-objs := $(call append_output_prefix,${${tgt}-objs})) \
  $(if ${DEBUG},$(info ${tgt}-objs = ${${tgt}-objs})) \
)
endef

# $1: input words, like: ${OUTPUT}a ${OUTPUT}b c /d
# output: a b c /d
define strip_output_prefix
$(foreach f,${1},$(patsubst ${OUTPUT}%,%,${f}))
endef

ifneq ($(call append_output_prefix,a c b),${OUTPUT}a ${OUTPUT}c ${OUTPUT}b)
  $(error append_output_prefix a b c failed)
endif
ifneq ($(call append_output_prefix,${OUTPUT}a c ${OUTPUT}b),${OUTPUT}a ${OUTPUT}c ${OUTPUT}b)
  $(error append_output_prefix ${OUTPUT}a c ${OUTPUT}b failed)
endif
ifneq ($(call append_output_prefix,${OUTPUT}),${OUTPUT})
  $(error append_output_prefix pass ${OUTPUT} failed)
endif
ifneq ($(call append_output_prefix,/a /b /c),/a /b /c)
  $(error append_output_prefix /a /b /c failed)
endif
ifneq ($(call append_output_prefix,/a b /c),/a ${OUTPUT}b /c)
  $(error append_output_prefix /a ${OUTPUT}b /c failed)
endif

ifneq ($(call strip_output_prefix,${OUTPUT}a ${OUTPUT}b c),a b c)
  $(error strip_output_prefix ${OUTPUT}a ${OUTPUT}b c failed)
endif
ifneq ($(call strip_output_prefix,${OUTPUT}a ${OUTPUT}b ${OUTPUT}c),a b c)
  $(error strip_output_prefix ${OUTPUT}a ${OUTPUT}b ${OUTPUT}c failed)
endif
ifneq ($(call strip_output_prefix,a b c),a b c)
  $(error strip_output_prefix a b c failed)
endif

xyz-objs := x y z
$(call target_objects_append_output_prefix,xyz)
ifneq ($(xyz-objs), ${OUTPUT}x ${OUTPUT}y ${OUTPUT}z)
  $(error target_objects_append_output_prefix xyz-objs=${xyz-objs} failed.)
endif

endif
