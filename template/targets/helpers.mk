# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Append definitions:
# - CFLAGS
# - CFLAGS_A
# - CFLAGS_SO
# - CFLAGS_NVCC
# - CFLAGS_HIPCC
# - CFLAGS_LSCC
# - CFLAGS_HTCC
# - LDFLAGS
# - LDFLAGS_A
# - LDFLAGS_SO
#
ifndef _TARGET_HELPERS_MK
_TARGET_HELPERS_MK = 1

include helpers.mk

$(call add_helpers_cflags, CFLAGS)
$(call add_helpers_cflags, CFLAGS_A)
$(call add_helpers_cflags, CFLAGS_SO)
$(call add_helpers_cflags, CFLAGS_NVCC)
$(call add_helpers_cflags, CFLAGS_HIPCC)
$(call add_helpers_cflags, CFLAGS_LSCC)
$(call add_helpers_cflags, CFLAGS_HTCC)

$(call add_helpers_ldflags, LDFLAGS)
$(call add_helpers_ldflags, LDFLAGS_A)
$(call add_helpers_ldflags, LDFLAGS_SO)

$(foreach helper, ${ALL_HELPERS}, \
  $(eval $(call add_helper_target,${helper})) \
)

endif
