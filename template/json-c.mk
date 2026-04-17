# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_JSON_C=[y|n]
#
ifndef _JSON_C_MK
_JSON_C_MK = 1

include define.mk

JSON_C_HDR := /usr/include/json-c/json.h

$(call check_file_and_def,${JSON_C_HDR},HAVE_JSON_C)

endif # end of _JSON_C_MK
