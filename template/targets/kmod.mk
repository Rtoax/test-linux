# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_KMOD_MK
_TARGET_KMOD_MK = 1

.PHONY: target-kmods
target-kmods:
	$(call log_tgt,KMOD,$(@))

endif
