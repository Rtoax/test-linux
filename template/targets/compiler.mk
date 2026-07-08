# SPDX-License-Identifier: GPL-3.0
#
# Input definitions:
#
ifndef _TARGET_COMPILER_MK
_TARGET_COMPILER_MK = 1

include compiler/macros.mk

$(CC)-macros.h:
	$(call log_tgt,MACRO HDR,$(@))
	$(call gen_compiler_macro_hdr,$(@))

endif
