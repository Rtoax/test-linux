# SPDX-License-Identifier: GPL-3.0
_TARGET_NVIDIA = 1
_SYSTEM_HAVE_NVIDIA_GPU :=

# Your system has Nvidia GPU card
ifneq ($(shell lspci | grep -oi nvidia),)
  _SYSTEM_HAVE_NVIDIA_GPU := 1
endif

NVCC := $(shell which nvcc 2>/dev/null)
CUOBJDUMP := $(shell which cuobjdump 2>/dev/null)
NVDISASM := $(shell which nvdisasm 2>/dev/null)
# After install CUDA, the /usr/local/cuda/ is symlink.
# refs
# - https://developer.download.nvidia.cn/compute/cuda/repos/rhel9/x86_64/
# - https://developer.nvidia.com/cuda-downloads
CUDA_ROOT := /usr/local/cuda/

ifneq ($(wildcard ${CUDA_ROOT}),)
  CUDA_ROOT := $(shell realpath ${CUDA_ROOT})
else
  CUDA_ROOT :=
endif

ifeq ($(NVCC),)
  ifneq ($(wildcard ${CUDA_ROOT}),)
    NVCC := ${CUDA_ROOT}/bin/nvcc
    CUOBJDUMP := ${CUDA_ROOT}/bin/cuobjdump
  endif
else
  NVCC := $(shell realpath ${NVCC})
  CUOBJDUMP := $(shell realpath ${CUOBJDUMP})
endif

ifeq ($(wildcard $(NVCC)),)
  $(error Not found nvcc, install cuda first)
endif

CUDA_VERSION_RAW := $(shell ${NVCC} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)
ifeq (${CUDA_VERSION_RAW},)
  $(error Not found CUDA Version in ${NVCC} --version)
endif
CUDA_VERSION_MAJOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$1}')
CUDA_VERSION_MINOR := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$2}')
CUDA_VERSION_PATCH := $(shell echo ${CUDA_VERSION_RAW} | awk -F '.' '{print $$3}')

cflags-nvcc-cubin := --cubin
cflags-nvcc-fatbin := --fatbin

CFLAGS_NVCC += -DHAVE_CUDA=1
CFLAGS_NVCC += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
CFLAGS_NVCC += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
CFLAGS_NVCC += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}

# NVCC: --gpu-architecture
# Pascal (sm_60+)
# Volta (sm_70+)
# Turing (sm_75+)
# Ampere (sm_80+)
# Ada Lovelace (sm_89+)
# Hopper (sm_90+)
ifneq (${_SYSTEM_HAVE_NVIDIA_GPU},)
  CFLAGS_NVCC += -arch=native
  LDFLAGS_NVCC += -arch=native
else
  CFLAGS_NVCC += -arch=sm_80
  LDFLAGS_NVCC += -arch=sm_80
endif

CFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -lcublas -lcublasLt
LDFLAGS_NVCC += -lcuda
LDFLAGS_NVCC += -lcufft
LDFLAGS_NVCC += -lcurand
LDFLAGS_NVCC += -lcusparse

ifdef ERROR
  CFLAGS_NVCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_NVCC += -DDEBUG=${DEBUG}
  $(info $(shell ${NVCC} --version))
  $(info NVCC = ${NVCC})
  $(info NVCC VERSION: $(shell ${NVCC} --version))
  $(info CUDA_VERSION_MAJOR = ${CUDA_VERSION_MAJOR})
  $(info CUDA_VERSION_MINOR = ${CUDA_VERSION_MINOR})
  $(info CUDA_VERSION_PATCH = ${CUDA_VERSION_PATCH})
  $(info cflags-nvcc-cubin = ${cflags-nvcc-cubin})
  $(info cflags-nvcc-fatbin = ${cflags-nvcc-fatbin})
  $(info CFLAGS_NVCC = ${CFLAGS_NVCC})
  $(info LDFLAGS_NVCC = ${LDFLAGS_NVCC})
endif

# NOTE: NVCC's cflags,ldflags is totally different from gcc/clang, thus, we
# don't use CFLAGS and LDFLAGS.
${OUTPUT}%.cu.o: %.cu | ${OUTPUT}
	$(call log_tgt_obj,NVCC,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cubin: %.cu | ${OUTPUT}
	$(call log_tgt_obj,CUBIN,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(cflags-nvcc-cubin) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.fatbin: %.cu | ${OUTPUT}
	$(call log_tgt_obj,FATBIN,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(cflags-nvcc-fatbin) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.sass.dump: ${OUTPUT}%.cu.o | ${OUTPUT}
	$(call log_tgt_obj,NV SASS,$(<),$(@))
	${Q}${CUOBJDUMP} --dump-sass $(<) > ${@}

${OUTPUT}%.ptx.dump: ${OUTPUT}%.cu.o | ${OUTPUT}
	$(call log_tgt_obj,NV PTX,$(<),$(@))
	${Q}${CUOBJDUMP} --dump-ptx $(<) > ${@}

${OUTPUT}%.E.cu: %.cu | ${OUTPUT}
	$(call log_tgt_obj,NVCC E,$(<),$(@))
	${Q}$(NVCC) -E -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

$(targets-nvcc): %:
	$(call log_tgt_exe,NVCC LD,$(<),$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS_NVCC) $(LDFLAGS_NVCC_$(*))
