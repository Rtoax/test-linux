# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - ASCIIDOC=[/usr/bin/asciidoc]
# - HAVE_ASCIIDOC=[y|n]
#
ifndef _ASCIIDOC_MK
_ASCIIDOC_MK = 1

include define.mk

$(call find_cmd_and_def,asciidoc)

endif # end of _ASCIIDOC_MK
