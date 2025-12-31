# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Input definitions:
# - __USE_C_HELPERS__=y
# - __USE_PROC_HELPERS__=y
# - __USE_SOCKET_HELPERS__=y
# - __USE_PTHREAD_HELPERS__=y
# - __USE_SCHED_HELPERS__=y
# - __USE_MMAP_HELPERS__=y
# - __USE_OOM_HELPERS__=y
# - __USE_TRACE_HELPERS__=y
# - __USE_KSYM_HELPERS__=y
# - __USE_BPF_HELPERS__=y
# - __USE_BTF_HELPERS__=y
# - __USE_BPF_INSN_SAMPLES__=y
# - __USE_CUDA_HELPERS__=y
# - __USE_HIP_HELPERS__=y
# - __USE_LUCA_HELPERS__=y
# - __USE_HPCC_HELPERS__=y
#
_TARGET_HELPERS_MK = 1

include helpers.mk

$(eval $(call add_helper_target,${C_HELPERS},${__USE_C_HELPERS__}))
$(eval $(call add_helper_target,${PROC_HELPERS},${__USE_PROC_HELPERS__}))
$(eval $(call add_helper_target,${SOCKET_HELPERS},${__USE_SOCKET_HELPERS__}))
$(eval $(call add_helper_target,${PTHREAD_HELPERS},${__USE_PTHREAD_HELPERS__}))
$(eval $(call add_helper_target,${SCHED_HELPERS},${__USE_SCHED_HELPERS__}))
$(eval $(call add_helper_target,${MMAP_HELPERS},${__USE_MMAP_HELPERS__}))
$(eval $(call add_helper_target,${OOM_HELPERS},${__USE_OOM_HELPERS__}))
$(eval $(call add_helper_target,${TRACE_HELPERS},${__USE_TRACE_HELPERS__}))
$(eval $(call add_helper_target,${KSYM_HELPERS},${__USE_KSYM_HELPERS__}))
$(eval $(call add_helper_target,${CUDA_HELPERS},${__USE_CUDA_HELPERS__}))
$(eval $(call add_helper_target,${HIP_HELPERS},${__USE_HIP_HELPERS__}))
$(eval $(call add_helper_target,${LUCA_HELPERS},${__USE_LUCA_HELPERS__}))
$(eval $(call add_helper_target,${HPCC_HELPERS},${__USE_HPCC_HELPERS__}))
$(eval $(call add_helper_target,${BPF_HELPERS},${__USE_BPF_HELPERS__}))
$(eval $(call add_helper_target,${BTF_HELPERS},${__USE_BTF_HELPERS__}))
$(eval $(call add_helper_target,${BPF_INSN_SAMPLES},${__USE_BPF_INSN_SAMPLES__}))
