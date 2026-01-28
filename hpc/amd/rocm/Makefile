# SPDX-License-Identifier: GPL-3.0
include amd/rocm.mk

target-shell-${HAVE_HIP} := version.sh
target-post-${HAVE_HIP} := hipcc-macros.h

hipcc-macros.h:
	$(call gen_hipcc_macro_hdr,hipcc-macros.h)

include main.mk
