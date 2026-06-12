# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - TMUX=[/usr/bin/tmux]
# - HAVE_TMUX=[y|n]
#
ifndef _TMUX_MK
_TMUX_MK = 1

include define.mk

$(call find_cmd_and_def,tmux)

endif # end of _TMUX_MK
