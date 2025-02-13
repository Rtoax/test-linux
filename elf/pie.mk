# SPDX-License-Identifier: GPL-3.0

ifdef PIE
  CFLAGS += -pie -fPIE
  LDFLAGS += -pie -fPIE
  MAKEFLAGS += PIE=1
endif

ifdef NOPIE
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
  MAKEFLAGS += NOPIE=1
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif
