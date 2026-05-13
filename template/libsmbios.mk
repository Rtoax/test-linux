# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
# ref: https://github.com/dell/libsmbios
#
# Output definitions:
# - HAVE_LIBSMBIOS=[y|n]
#
ifndef _LIBSMBIOS_MK
_LIBSMBIOS_MK = 1

include ldconfig.mk
include define.mk

export HAVE_LIBSMBIOS := $(call have_library,libsmbios_c.so)
$(call check_file_and_def, /usr/include/smbios_c, HAVE_LIBSMBIOS_H)

ifdef DEBUG
  $(info HAVE_LIBSMBIOS = ${HAVE_LIBSMBIOS})
endif

endif
