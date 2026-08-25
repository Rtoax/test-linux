# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_VDSO_MK
_TARGET_VDSO_MK = 1

include vdso.mk

${VDSO_NAME}:
	@$(call log_tgt,VDSO,$(@))
	$(call gen_vdso_elf,${@})

endif
