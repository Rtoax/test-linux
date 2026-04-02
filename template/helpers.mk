# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# Note: _helpers.{c,h} better not use symlinks, you could check with:
#
#   $ find -name '*_helpers.c' -exec basename {} \; | sort
#
# Input definitions:
# - STATIC=1			Compile static library instead of dynamic library.
#
# Output definitions:
# - helpers-cflags=
# - helpers-ldflags=
# - KSYM_HELPERS
# - PROC_HELPERS
# - SOCKET_HELPERS
# - PTHREAD_HELPERS
# - SCHED_HELPERS
# - MMAP_HELPERS
# - OOM_HELPERS
# - TRACE_HELPERS
# - CUDA_HELPERS
# - HIP_HELPERS
# - LUCA_HELPERS
# - HPCC_HELPERS
# - BPF_HELPERS
# - BTF_HELPERS
# - BPF_INSN_SAMPLES
#
# Functions:
# - add_helpers_cflags()
# - add_helpers_ldflags()
# - add_helper_target()
#
ifndef _HELPERS_MK
_HELPERS_MK = 1

include dir.mk
include mkflags.mk
include make.mk

helpers-cflags :=
helpers-ldflags :=

ifdef STATIC
  LIB_TYPE = a
else
  LIB_TYPE = so
endif

export C_HELPERS := ${TOPDIR}/libs/libtest-linux-c.${LIB_TYPE}
export KSYM_HELPERS := ${TOPDIR}/libs/libksym_helpers.${LIB_TYPE}
export PROC_HELPERS := ${TOPDIR}/libs/libproc_helpers.${LIB_TYPE}
export SOCKET_HELPERS := ${TOPDIR}/libs/libsocket_helpers.${LIB_TYPE}
export PTHREAD_HELPERS := ${TOPDIR}/libs/libpthread_helpers.${LIB_TYPE}
export SCHED_HELPERS := ${TOPDIR}/libs/libsched_helpers.${LIB_TYPE}
export MMAP_HELPERS := ${TOPDIR}/libs/libmmap_helpers.${LIB_TYPE}
export OOM_HELPERS := ${TOPDIR}/mm/oom/liboom_helpers.${LIB_TYPE}
export TRACE_HELPERS := ${TOPDIR}/libs/libtrace_helpers.${LIB_TYPE}
export CUDA_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libcuda_helper.${LIB_TYPE}
export HIP_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libhip_helper.${LIB_TYPE}
export LUCA_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libluca_helper.${LIB_TYPE}
export HPCC_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libhpcc_helper.${LIB_TYPE}
export BPF_HELPERS := ${TOPDIR}/syscall/samples/bpf/libbpf_helpers.${LIB_TYPE}
export BTF_HELPERS := ${TOPDIR}/bpf/btf/libbtf_helpers.${LIB_TYPE}
export BPF_INSN_SAMPLES := ${TOPDIR}/bpf/insn/samples/libbpf_insn_samples.${LIB_TYPE}

export ALL_HELPERS := \
		${C_HELPERS} \
		${SOCKET_HELPERS} \
		${PTHREAD_HELPERS} \
		${SCHED_HELPERS} \
		${MMAP_HELPERS} \
		${OOM_HELPERS} \
		${TRACE_HELPERS} \
		${CUDA_HELPERS} \
		${HIP_HELPERS} \
		${LUCA_HELPERS} \
		${HPCC_HELPERS} \
		${BPF_HELPERS} \
		${BTF_HELPERS} \
		${BPF_INSN_SAMPLES}

$(foreach helper, ${ALL_HELPERS}, $(eval helpers-cflags += -I$(shell dirname ${helper})))

$(foreach helper, ${ALL_HELPERS}, \
  $(if ${STATIC}, \
    $(eval helpers-ldflags += ${helper}), \
    $(eval helpers-ldflags += -Wl,-rpath,$(shell dirname ${helper})) \
  ) \
)

export helpers-cflags
export helpers-ldflags

# $1: cflags's name, like CFLAGS, CFLAGS_SO
define add_helpers_cflags
$(eval ${1} += ${helpers-cflags})
endef

# $1: ldflags's name, like LDFLAGS, LDFLAGS_SO
define add_helpers_ldflags
$(eval ${1} += ${helpers-ldflags})
endef

# $1 - helper library absolute path, like: /path/to/liba.so
define add_helper_target
$(if ${DEBUG}, $(info Add helper $1))
${1}:
	${Q}${MAKE} --no-print-directory --silent ${SUBMKFLAGS} -C $$(shell dirname ${1}) $$(shell basename ${1})
endef

ifdef DEBUG
  $(info ALL_HELPERS = ${ALL_HELPERS})
  $(info C_HELPERS = ${C_HELPERS})
  $(info KSYM_HELPERS = ${KSYM_HELPERS})
  $(info PROC_HELPERS = ${PROC_HELPERS})
  $(info SOCKET_HELPERS = ${SOCKET_HELPERS})
  $(info PTHREAD_HELPERS = ${PTHREAD_HELPERS})
  $(info SCHED_HELPERS = ${SCHED_HELPERS})
  $(info MMAP_HELPERS = ${MMAP_HELPERS})
  $(info OOM_HELPERS = ${OOM_HELPERS})
  $(info TRACE_HELPERS = ${TRACE_HELPERS})
  $(info CUDA_HELPERS = ${CUDA_HELPERS})
  $(info HIP_HELPERS = ${HIP_HELPERS})
  $(info LUCA_HELPERS = ${LUCA_HELPERS})
  $(info HPCC_HELPERS = ${HPCC_HELPERS})
  $(info BPF_HELPERS = ${BPF_HELPERS})
  $(info BTF_HELPERS = ${BTF_HELPERS})
  $(info BPF_INSN_SAMPLES = ${BPF_INSN_SAMPLES})
  $(info helpers-cflags = ${helpers-cflags})
  $(info helpers-ldflags = ${helpers-ldflags})
endif

endif
