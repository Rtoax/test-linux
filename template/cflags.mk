# SPDX-License-Identifier: GPL-3.0
#
# Append flags:
# - dep_cflags=
#
ifndef _CFLAGS_MK
export _CFLAGS_MK = 1

dep_cflags = -MMD -MT $(@) -MF $(@:=.d)

ifdef DEBUG
  $(info dep_cflags = ${dep_cflags})
endif

export dep_cflags

endif # _CFLAGS_MK
