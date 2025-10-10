# SPDX-License-Identifier: GPL-3.0
# This makefile use to compile Nvidia targets.
#
# Targets list:
# .cu.o
# .ptx
# .cu.cpp.ii
# .cubin
# .fatbin
# .nv_fatbin
# .nvFatBinSegment
# .cu.ptx.dump
# .cu.sass.dump
# .E.cu
# targets-nvcc

_TARGET_NVIDIA = 1
_SYSTEM_HAVE_NVIDIA_GPU :=

# Your system has Nvidia GPU card
ifneq ($(shell lspci | grep -oi nvidia),)
  _SYSTEM_HAVE_NVIDIA_GPU := 1
endif

include ${TEMPLATE_DIR}/../hpc/nvidia/cuda/cuda.mk

cflags-nvcc-cubin := --cubin
cflags-nvcc-fatbin := --fatbin

CFLAGS_NVCC += -DHAVE_CUDA=1
ifdef HAVE_NCCL
  CFLAGS_NVCC += -DHAVE_NCCL=1
endif
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

# Use to test fakeCUDA
ldflags-cudart := --cudart shared

CFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -Wno-deprecated-gpu-targets
LDFLAGS_NVCC += -lcublas -lcublasLt
LDFLAGS_NVCC += -lcuda
LDFLAGS_NVCC += -lcufft
LDFLAGS_NVCC += -lcurand
LDFLAGS_NVCC += -lcusparse
ifdef HAVE_NCCL
  LDFLAGS_NVCC += -lnccl
endif
LDFLAGS_NVCC += ${ldflags-cudart}

ifdef ERROR
  CFLAGS_NVCC += -DERROR=1
endif

ifdef DEBUG
  CFLAGS_NVCC += -DDEBUG=${DEBUG}
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

${OUTPUT}%.ptx: %.cu | ${OUTPUT}
	$(call log_tgt_obj,PTX,$(<),$(@))
	${Q}$(NVCC) -ptx -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cu.cpp.ii: %.cu | ${OUTPUT}
	$(call log_tgt_obj,II,$(<),$(@))
	${Q}$(NVCC) -cuda -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.cubin: %.cu | ${OUTPUT}
	$(call log_tgt_obj,CUBIN,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(cflags-nvcc-cubin) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

${OUTPUT}%.fatbin: %.cu | ${OUTPUT}
	$(call log_tgt_obj,FATBIN,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(cflags-nvcc-fatbin) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

# Example format of nv_fatbin and nvFatBinSegment, see:
# commit 0f8f83ac8109 ("targets/nvidia.mk: add .nv_fatbin and .nvFatBinSegment targets")
${OUTPUT}%.nv_fatbin: % | ${OUTPUT}
	$(call log_tgt_obj,NV FATBIN,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.nv_fatbin $(<) $(@)

${OUTPUT}%.nvFatBinSegment: % | ${OUTPUT}
	$(call log_tgt_obj,NV FATBIN SEG,$(<),$(@))
	${Q}$(OBJCOPY) -O binary --only-section=.nvFatBinSegment $(<) $(@)

${OUTPUT}%.cu.sass.dump: ${OUTPUT}%.cu.o | ${OUTPUT}
	$(call log_tgt_obj,NV SASS,$(<),$(@))
	${Q}${CUOBJDUMP} --dump-sass $(<) > ${@}

${OUTPUT}%.cu.ptx.dump: ${OUTPUT}%.cu.o | ${OUTPUT}
	$(call log_tgt_obj,NV PTX,$(<),$(@))
	${Q}${CUOBJDUMP} --dump-ptx $(<) > ${@}

${OUTPUT}%.E.cu: %.cu | ${OUTPUT}
	$(call log_tgt_obj,NVCC E,$(<),$(@))
	${Q}$(NVCC) -E -o $(@) -c $(<) $(CFLAGS_NVCC) $(CFLAGS_NVCC_$(*))

$(targets-nvcc): %:
	$(call log_tgt_exe,NVCC LD,$(<),$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS_NVCC) $(LDFLAGS_NVCC_$(*))
