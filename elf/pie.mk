# SPDX-License-Identifier: GPL-3.0
ifeq ($(CC),)
  $(error Not define CC)
endif

ifdef PIE
  # clang: not support -pie in cflags
  ifeq ($(CC),gcc)
    CFLAGS += -pie
  endif
  CFLAGS += -fPIE
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
