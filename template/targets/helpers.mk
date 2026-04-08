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

$(eval $(call add_helper_target,${TLC_HELPERS}))
$(eval $(call add_helper_target,${KSYM_HELPERS}))
$(eval $(call add_helper_target,${PROC_HELPERS}))
$(eval $(call add_helper_target,${SOCKET_HELPERS}))
$(eval $(call add_helper_target,${PTHREAD_HELPERS}))
$(eval $(call add_helper_target,${PCIE_HELPERS}))
$(eval $(call add_helper_target,${SCHED_HELPERS}))
$(eval $(call add_helper_target,${MMAP_HELPERS}))
$(eval $(call add_helper_target,${OOM_HELPERS}))
$(eval $(call add_helper_target,${QCOW2_HELPERS}))
$(eval $(call add_helper_target,${TRACE_HELPERS}))
$(eval $(call add_helper_target,${CUDA_HELPERS}))
$(eval $(call add_helper_target,${CGROUP_HELPERS}))
$(eval $(call add_helper_target,${HIP_HELPERS}))
$(eval $(call add_helper_target,${LUCA_HELPERS}))
$(eval $(call add_helper_target,${HPCC_HELPERS}))
$(eval $(call add_helper_target,${BPF_HELPERS}))
$(eval $(call add_helper_target,${BTF_HELPERS}))
$(eval $(call add_helper_target,${BPF_INSN_SAMPLES}))

endif
