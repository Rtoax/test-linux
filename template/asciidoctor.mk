# SPDX-License-Identifier: GPL-3.0
#
# https://asciidoctor.org
#
# Output definitions:
# - ASCIIDOCTOR=[/usr/bin/asciidoctor]
# - HAVE_ASCIIDOCTOR=[y|n]
#
ifndef _ASCIIDOCTOR_MK
_ASCIIDOCTOR_MK = 1

include define.mk

$(call find_cmd_and_def,asciidoctor)

endif # end of _ASCIIDOCTOR_MK
