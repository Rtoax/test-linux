# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2025 Rong Tao
#
# Note: _helpers.{c,h} better not use symlinks, you could check with:
#
#   $ find -name '*_helpers.c' -exec basename {} \; | sort
#
# Input definitions:
# - STATIC=1			Compile static library instead of dynamic library.
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
# Output definitions:
# - PROC_HELPERS
# - SOCKET_HELPERS
# - PTHREAD_HELPERS
# - SCHED_HELPERS
# - MMAP_HELPERS
# - OOM_HELPERS
# - TRACE_HELPERS
# - KSYM_HELPERS
# - CUDA_HELPERS
# - HIP_HELPERS
# - LUCA_HELPERS
# - HPCC_HELPERS
# - BPF_HELPERS
# - BTF_HELPERS
# - BPF_INSN_SAMPLES
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
_HELPERS = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

# $1 - helper library absolute path
# $2 - turn on with 'y', otherwise turn off
define add_helper_target
ifeq ($(2),y)
  CFLAGS += -I$$(shell dirname ${1})
  CFLAGS_A += -I$$(shell dirname ${1})
  CFLAGS_SO += -I$$(shell dirname ${1})
  CFLAGS_NVCC += -I$$(shell dirname ${1})
  CFLAGS_HIPCC += -I$$(shell dirname ${1})
  CFLAGS_LSCC += -I$$(shell dirname ${1})
  CFLAGS_HTCC += -I$$(shell dirname ${1})
  ifdef DEBUG
    $$(info Use helper $1)
  endif
  ifdef STATIC
    LDFLAGS += ${1}
  else
    LDFLAGS += -Wl,-rpath,$$(shell dirname ${1})
  endif
endif
${1}:
	@make --no-print-directory --silent -C $$(shell dirname ${1}) $$(shell basename ${1})
endef

ifdef STATIC
  LIB_TYPE = a
else
  LIB_TYPE = so
endif

export C_HELPERS := ${TOPDIR}/libs/libtest-linux-c.${LIB_TYPE}
export PROC_HELPERS := ${TOPDIR}/fs/procfs/libproc_helpers.${LIB_TYPE}
export SOCKET_HELPERS := ${TOPDIR}/ipc/socket/libsocket_helpers.${LIB_TYPE}
export PTHREAD_HELPERS := ${TOPDIR}/glibc/pthread/libpthread_helpers.${LIB_TYPE}
export SCHED_HELPERS := ${TOPDIR}/syscall/samples/sched/libsched_helpers.${LIB_TYPE}
export MMAP_HELPERS := ${TOPDIR}/syscall/samples/mm/mmap/libmmap_helpers.${LIB_TYPE}
export OOM_HELPERS := ${TOPDIR}/mm/oom/liboom_helpers.${LIB_TYPE}
export TRACE_HELPERS := ${TOPDIR}/bpf/libbpf/libtrace_helpers.${LIB_TYPE}
export KSYM_HELPERS := ${TOPDIR}/fs/procfs/kallsyms/libksym_helpers.${LIB_TYPE}
export CUDA_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libcuda_helper.${LIB_TYPE}
export HIP_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libhip_helper.${LIB_TYPE}
export LUCA_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libluca_helper.${LIB_TYPE}
export HPCC_HELPERS := ${TOPDIR}/hpc/nvidia/cuda/libhpcc_helper.${LIB_TYPE}
export BPF_HELPERS := ${TOPDIR}/syscall/samples/bpf/libbpf_helpers.${LIB_TYPE}
export BTF_HELPERS := ${TOPDIR}/bpf/btf/libbtf_helpers.${LIB_TYPE}
export BPF_INSN_SAMPLES := ${TOPDIR}/bpf/insn/samples/libbpf_insn_samples.${LIB_TYPE}

ifdef DEBUG
  $(info C_HELPERS = ${C_HELPERS})
  $(info PROC_HELPERS = ${PROC_HELPERS})
  $(info SOCKET_HELPERS = ${SOCKET_HELPERS})
  $(info PTHREAD_HELPERS = ${PTHREAD_HELPERS})
  $(info SCHED_HELPERS = ${SCHED_HELPERS})
  $(info MMAP_HELPERS = ${MMAP_HELPERS})
  $(info OOM_HELPERS = ${OOM_HELPERS})
  $(info TRACE_HELPERS = ${TRACE_HELPERS})
  $(info KSYM_HELPERS = ${KSYM_HELPERS})
  $(info CUDA_HELPERS = ${CUDA_HELPERS})
  $(info HIP_HELPERS = ${HIP_HELPERS})
  $(info LUCA_HELPERS = ${LUCA_HELPERS})
  $(info HPCC_HELPERS = ${HPCC_HELPERS})
  $(info BPF_HELPERS = ${BPF_HELPERS})
  $(info BTF_HELPERS = ${BTF_HELPERS})
  $(info BPF_INSN_SAMPLES = ${BPF_INSN_SAMPLES})
endif
