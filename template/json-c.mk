# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_JSON_C=[y|n]
# - json-c-cflags=
# - json-c-ldflags=
#
ifndef _JSON_C_MK
_JSON_C_MK = 1

include define.mk

JSON_C_HDR := /usr/include/json-c/json.h

$(call check_file_and_def,${JSON_C_HDR},HAVE_JSON_C)

json-c-cflags := $(shell pkg-config --cflags json-c)
json-c-ldflags := $(shell pkg-config --libs json-c)

ifdef DEBUG
  $(info json-c-cflags = ${json-c-cflags})
  $(info json-c-ldflags = ${json-c-ldflags})
endif

export json-c-cflags
export json-c-ldflags

endif # end of _JSON_C_MK
