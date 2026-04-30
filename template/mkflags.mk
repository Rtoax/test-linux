# SPDX-License-Identifier: GPL-3.0
#
# Append flags:
# - MAKEFLAGS+=
# - SUBMKFLAGS+=
#
ifndef _MKFLAGS_MK
export _MKFLAGS_MK = 1

SUBMKFLAGS ?=

define append_mkflags
ifdef ${1}
  SUBMKFLAGS += ${1}=$${${1}}
  MAKEFLAGS += ${1}=$${${1}}
endif
endef

$(eval $(call append_mkflags,V))
$(eval $(call append_mkflags,DEBUG))
$(eval $(call append_mkflags,ERROR))
$(eval $(call append_mkflags,KMOD))
$(eval $(call append_mkflags,OUTPUT))
$(eval $(call append_mkflags,M32))
$(eval $(call append_mkflags,FORCE))
$(eval $(call append_mkflags,STATIC))

ifdef DEBUG
  $(info SUBMKFLAGS = ${SUBMKFLAGS})
  $(info MAKEFLAGS = ${MAKEFLAGS})
endif

export SUBMKFLAGS MAKEFLAGS

endif # _MKFLAGS_MK
