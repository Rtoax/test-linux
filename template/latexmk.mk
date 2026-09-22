# SPDX-License-Identifier: GPL-3.0
# https://www.cantab.net/users/johncollins/latexmk/
#
# Output definitions:
# - LATEXMK=[/usr/bin/latexmk]
# - HAVE_LATEXMK=[y|n]
#
ifndef _LATEXMK_MK
_LATEXMK_MK = 1

include define.mk

$(call find_cmd_and_def,latexmk)

endif # end of _LATEXMK_MK
