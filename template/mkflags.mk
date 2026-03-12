# SPDX-License-Identifier: GPL-3.0
#
# Append flags:
# - SUBMKFLAGS=
#
ifndef _MKFLAGS_MK
export _MKFLAGS_MK = 1

SUBMKFLAGS ?=

define add_submkflags
ifdef ${1}
  SUBMKFLAGS += ${1}=$${${1}}
endif
endef

$(eval $(call add_submkflags,V))
$(eval $(call add_submkflags,DEBUG))
$(eval $(call add_submkflags,ERROR))
$(eval $(call add_submkflags,KMOD))
$(eval $(call add_submkflags,OUTPUT))

ifdef DEBUG
  $(info SUBMKFLAGS = ${SUBMKFLAGS})
endif

export SUBMKFLAGS

endif # _MKFLAGS_MK
