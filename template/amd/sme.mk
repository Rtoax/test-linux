# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# AMD SME (Secure Memory Encryption) @TEE
#
# Definitions:
# - CPU_HAVE_SME=[y]
#
ifndef _AMD_SME_MK
_AMD_SME_MK = 1

include bits/cpu-feature.mk

$(call define_cpufeature,sme)

endif # end of _AMD_SME_MK
