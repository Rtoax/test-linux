# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# AMD Secure Encrypted Virtualization (SEV) @TEE
#
# Definitions:
# - CPU_HAVE_SEV=[y]
# - CPU_HAVE_SEV_ES=[y]
#
ifndef _AMD_SEV_MK
_AMD_SEV_MK = 1

include bits/cpu-feature.mk

$(call define_cpufeature,sev)
$(call define_cpufeature,sev_es)

endif # end of _AMD_SEV_MK
