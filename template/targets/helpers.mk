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
#
ifndef _TARGET_HELPERS_MK
_TARGET_HELPERS_MK = 1

include helpers.mk
include mkflags.mk
include make.mk

# $1 - helper library absolute path
define add_helper_target
CFLAGS += -I$(shell dirname ${1})
CFLAGS_A += -I$(shell dirname ${1})
CFLAGS_SO += -I$(shell dirname ${1})
CFLAGS_NVCC += -I$(shell dirname ${1})
CFLAGS_HIPCC += -I$(shell dirname ${1})
CFLAGS_LSCC += -I$(shell dirname ${1})
CFLAGS_HTCC += -I$(shell dirname ${1})
ifdef DEBUG
  $$(info Use helper $1)
endif
ifdef STATIC
  LDFLAGS += ${1}
else
  LDFLAGS += -Wl,-rpath,$$(shell dirname ${1})
endif
${1}:
	${Q}${MAKE} --no-print-directory --silent ${SUBMKFLAGS} -C $$(shell dirname ${1}) $$(shell basename ${1})
endef

$(eval $(call add_helper_target,${C_HELPERS}))
$(eval $(call add_helper_target,${PROC_HELPERS}))
$(eval $(call add_helper_target,${SOCKET_HELPERS}))
$(eval $(call add_helper_target,${PTHREAD_HELPERS}))
$(eval $(call add_helper_target,${SCHED_HELPERS}))
$(eval $(call add_helper_target,${MMAP_HELPERS}))
$(eval $(call add_helper_target,${OOM_HELPERS}))
$(eval $(call add_helper_target,${TRACE_HELPERS}))
$(eval $(call add_helper_target,${KSYM_HELPERS}))
$(eval $(call add_helper_target,${CUDA_HELPERS}))
$(eval $(call add_helper_target,${HIP_HELPERS}))
$(eval $(call add_helper_target,${LUCA_HELPERS}))
$(eval $(call add_helper_target,${HPCC_HELPERS}))
$(eval $(call add_helper_target,${BPF_HELPERS}))
$(eval $(call add_helper_target,${BTF_HELPERS}))
$(eval $(call add_helper_target,${BPF_INSN_SAMPLES}))

endif
