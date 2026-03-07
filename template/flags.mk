# SPDX-License-Identifier: GPL-3.0
#
# Append flags:
# - SUBMKFLAGS
#
ifndef _FLAGS_MK
_FLAGS_MK = 1

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

ifdef DEBUG
  $(info SUBMKFLAGS = ${SUBMKFLAGS})
endif

export SUBMKFLAGS

endif # _FLAGS_MK
