# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
ifndef _TERMINAL_MK
_TERMINAL_MK = 1

TERM := $(shell echo $${TERM})

ifdef DEBUG
  $(info TERM = ${TERM})
endif

endif # end of _TERMINAL_MK
