# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBDWARF=[y|n]
# - libdwarf-cflags=
# - libdwarf-ldflags=
#
ifndef _LIBDWARF_MK
_LIBDWARF_MK = 1

libdwarf-cflags := $(shell pkg-config --cflags libdwarf 2>/dev/null)
libdwarf-ldflags := $(shell pkg-config --libs libdwarf 2>/dev/null)

ifneq (${libdwarf-ldflags},)
  libdwarf-cflags += -DHAVE_LIBDWARF=1
  export HAVE_LIBDWARF := y
else
  $(warning "WARNING: You need to install libdwarf")
  export HAVE_LIBDWARF := n
endif

ifdef DEBUG
  $(info HAVE_LIBDWARF = ${HAVE_LIBDWARF})
  $(info libdwarf-cflags = ${libdwarf-cflags})
  $(info libdwarf-ldflags = ${libdwarf-ldflags})
endif

endif
