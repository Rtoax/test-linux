# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - VIM=[/usr/bin/vim]
# - HAVE_VIM=[y|n]
#
# - XXD=[/usr/bin/xxd]
# - HAVE_XXD=[y|n]
#
ifndef _VIM_MK
_VIM_MK = 1

include define.mk

$(call find_cmd_and_def,vim)
$(call find_cmd_and_def,xxd)

endif # end of _VIM_MK
