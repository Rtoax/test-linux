# SPDX-License-Identifier: GPL-3.0
#
# Append flags:
# - SUBMKFLAGS
#
ifndef _FLAGS_MK
_FLAGS_MK = 1

SUBMKFLAGS ?=

ifdef V
  SUBMKFLAGS += V=${V}
endif
ifdef DEBUG
  SUBMKFLAGS += DEBUG=${DEBUG}
endif
ifdef ERROR
  SUBMKFLAGS += ERROR=${ERROR}
endif

export SUBMKFLAGS

endif
