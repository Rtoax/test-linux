# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_READLINE=[y|n]
# - readline-ldflags=
#
ifndef _READLINE_MK
_READLINE_MK = 1

include define.mk

READLINE_HDR := /usr/include/readline/readline.h

$(call check_file_and_def,${READLINE_HDR},HAVE_READLINE)

readline-ldflags := -lreadline -lutil -ltermcap -lhistory

endif # end of _READLINE_MK
