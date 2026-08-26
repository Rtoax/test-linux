# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - EU_READELF=[/usr/bin/eu-readelf]
# - HAVE_EU_READELF=[y|n]
#
ifndef _ELFUTILS_MK
_ELFUTILS_MK = 1

include define.mk

$(call find_cmd_and_def,eu-readelf)

endif # end of _ELFUTILS_MK
