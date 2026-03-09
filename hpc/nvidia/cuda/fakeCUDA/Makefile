# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

subdir-y := frontend

include nvidia/cuda.mk
include nvidia/nccl.mk
include amd/rocm.mk
include metax/hpcc.mk
include cestc/luca.mk

libso-hpcc := libhccompiler.so
libso-hpcc += libhcruntime.so
libso-hpcc += libhcblas.so
libso-hpcc += libhcblasLt.so
libso-hpcc += libhcfft.so
libso-hpcc += libhcrand.so
libso-hpcc += libhcsparse.so
libso-hpcc += libhcsolver.so
libso-hpcc += libhccl.so

libso-luca := liblccompiler.so
libso-luca += liblcruntime.so
libso-luca += liblcblas.so
libso-luca += liblcblasLt.so
libso-luca += liblcfft.so
libso-luca += liblcrand.so
libso-luca += liblcsparse.so
libso-luca += liblcsolver.so
libso-luca += liblccl.so

target-libso-cpp-${HAVE_CUDA} := libcuda.so.1
target-libso-cpp-${HAVE_CUDA} += libcudart.so.12 libcudart.so.13
target-libso-cpp-${HAVE_CUDA} += libcublas.so.12 libcublas.so.13
target-libso-cpp-${HAVE_CUDA} += libcublasLt.so.12 libcublasLt.so.13
target-libso-cpp-${HAVE_CUDA} += libcufft.so.11 libcufft.so.12
target-libso-cpp-${HAVE_CUDA} += libcurand.so.10
target-libso-cpp-${HAVE_CUDA} += libcusparse.so.12
target-libso-cpp-${HAVE_CUDA} += libcusolver.so.12
target-libso-cpp-${HAVE_NCCL} += libnccl.so.2

libso-hip := libamdhip64.so.5 libamdhip64.so.6
libso-hip += libhipfft.so.0 librocfft.so.0
libso-hip += libhipsparse.so.1 librocsparse.so.1
libso-hip += libhipsolver.so.0
libso-hip += libhiprand.so.1
libso-hip += libhipblas.so.2 libhipblaslt.so.0
libso-hip += librccl.so.1

CXXFLAGS_SO_CUDA_SPECIAL :=
CXXFLAGS_SO_HIP_SPECIAL :=
CXXFLAGS_SO_HPCC_SPECIAL :=
CXXFLAGS_SO_LUCA_SPECIAL :=

CXXFLAGS_SO += -I../
# See commit d3d0fe465313 ("fakeCUDA: cuda_compat.h: add __NOT_USE_FP8__ macro to fix HIP compile errors")
CXXFLAGS_SO += -D__NOT_USE_FP8__
ifdef HAVE_HIPSOLVER
  CXXFLAGS_SO += -DHAVE_HIPSOLVER=1
endif
ifdef HAVE_HIPBLASLT
  CXXFLAGS_SO += -DHAVE_HIPBLASLT=1
endif
ifdef HAVE_RCCL
  CXXFLAGS_SO += -DHAVE_RCCL=1
endif
ifdef HAVE_NCCL
  CXXFLAGS_SO += -DHAVE_NCCL=1
endif
ifdef HAVE_NVRTC
  CXXFLAGS_SO += -DHAVE_NVRTC=1
endif

ifdef HAVE_HPCC
  $(info HAVE_HPCC)
  target-libso-cpp-y += ${libso-hpcc}

  CXXFLAGS_SO_HPCC_SPECIAL += -I../adapter/include/
  CXXFLAGS_SO_HPCC_SPECIAL += -I${HPCC_ROOT}/include/
  CXXFLAGS_SO_HPCC_SPECIAL += -I${HPCC_ROOT}/include/common/
  CXXFLAGS_SO_HPCC_SPECIAL += -I${HPCC_ROOT}/include/hcr/
  CXXFLAGS_SO_HPCC_SPECIAL += -I${HPCC_ROOT}/include/hcsparse/
  CXXFLAGS_SO_HPCC_SPECIAL += -I${HPCC_ROOT}/include/hcblas/

  CXXFLAGS_SO += -DHAVE_HPCC=1
endif

ifdef HAVE_LUCA
  $(info HAVE_LUCA)
  target-libso-cpp-y += ${libso-luca}

  CXXFLAGS_SO_LUCA_SPECIAL += -I../adapter/include/
  CXXFLAGS_SO_LUCA_SPECIAL += -I${LUCA_ROOT}/include/
  CXXFLAGS_SO_LUCA_SPECIAL += -I${LUCA_ROOT}/include/common/
  CXXFLAGS_SO_LUCA_SPECIAL += -I${LUCA_ROOT}/include/lcr/
  CXXFLAGS_SO_LUCA_SPECIAL += -I${LUCA_ROOT}/include/lcsparse/
  CXXFLAGS_SO_LUCA_SPECIAL += -I${LUCA_ROOT}/include/lcblas/
  ifdef LUCA_PHASE_II_PROJECT
    CXXFLAGS_SO_LUCA_SPECIAL += -DLUCA_PHASE_II_PROJECT=1
  endif

  CXXFLAGS_SO += -DHAVE_LUCA=1
endif

ifeq (${HAVE_CUDA},y)
  $(info HAVE_CUDA)
  CXXFLAGS_SO_CUDA_SPECIAL += -I${CUDA_ROOT}/include/
  CXXFLAGS_SO += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
  CXXFLAGS_SO += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
  CXXFLAGS_SO += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}
  CXXFLAGS_SO += -DHAVE_CUDA=1
endif

ifeq (${HAVE_HIP},y)
  $(info HAVE_HIP)
  target-libso-cpp-y += ${libso-hip}

  CXXFLAGS_SO_HIP_SPECIAL += -I../adapter/include/
  CXXFLAGS_SO += -I.
  CXXFLAGS_SO += -DHAVE_HIP=1
endif

# HPCC
CXXFLAGS_SO_cuda-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_cuda-module-mgmt-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_blas-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_blasLt-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_fft-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_rand-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_runtime-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_runtime_event-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_runtime_memory-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_runtime_internal-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_solver-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_sparse-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
CXXFLAGS_SO_nccl-hpcc := ${CXXFLAGS_SO_HPCC_SPECIAL}
LDXXFLAGS_SO_libhccompiler.so := -Wl,--version-script=libhccompiler.map
LDXXFLAGS_SO_libhccl.so := -Wl,--version-script=libhccl.map
LDXXFLAGS_SO_libhcruntime.so := -Wl,--version-script=libhcruntime.map
LDXXFLAGS_SO_libhcblas.so := -Wl,--version-script=libhcblas.map
LDXXFLAGS_SO_libhcblasLt.so := -Wl,--version-script=libhcblasLt.map
LDXXFLAGS_SO_libhcfft.so := -Wl,--version-script=libhcfft.map
LDXXFLAGS_SO_libhcrand.so := -Wl,--version-script=libhcrand.map
LDXXFLAGS_SO_libhcsparse.so := -Wl,--version-script=libhcsparse.map
LDXXFLAGS_SO_libhcsolver.so := -Wl,--version-script=libhcsolver.map

# LUCA
CXXFLAGS_SO_cuda-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_cuda-module-mgmt-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_blas-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_blasLt-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_fft-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_rand-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_runtime-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_runtime_event-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_runtime_memory-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_runtime_internal-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_solver-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_sparse-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
CXXFLAGS_SO_nccl-luca := ${CXXFLAGS_SO_LUCA_SPECIAL}
LDXXFLAGS_SO_liblccompiler.so := -Wl,--version-script=liblccompiler.map
LDXXFLAGS_SO_liblcruntime.so := -Wl,--version-script=liblcruntime.map
LDXXFLAGS_SO_liblcblas.so := -Wl,--version-script=liblcblas.map
LDXXFLAGS_SO_liblcblasLt.so := -Wl,--version-script=liblcblasLt.map
LDXXFLAGS_SO_liblcfft.so := -Wl,--version-script=liblcfft.map
LDXXFLAGS_SO_liblcrand.so := -Wl,--version-script=liblcrand.map
LDXXFLAGS_SO_liblcsparse.so := -Wl,--version-script=liblcsparse.map
LDXXFLAGS_SO_liblcsolver.so := -Wl,--version-script=liblcsolver.map
LDXXFLAGS_SO_liblccl.so := -Wl,--version-script=liblccl.map

# CUDA
CXXFLAGS_SO_cuda := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_cuda-module-mgmt := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_blas := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_blasLt := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_fft := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_rand := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_runtime := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_runtime_event := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_runtime_memory := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_runtime_internal := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_solver := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_sparse := ${CXXFLAGS_SO_CUDA_SPECIAL}
CXXFLAGS_SO_nccl := ${CXXFLAGS_SO_CUDA_SPECIAL}
LDXXFLAGS_SO_libcuda.so.1 := -Wl,--version-script=libcuda.map
LDXXFLAGS_SO_libcudart.so.12 := -Wl,--version-script=libcudart.12.map
LDXXFLAGS_SO_libcudart.so.13 := -Wl,--version-script=libcudart.13.map
LDXXFLAGS_SO_libcublas.so.12 := -Wl,--version-script=libcublas.12.map
LDXXFLAGS_SO_libcublas.so.13 := -Wl,--version-script=libcublas.13.map
LDXXFLAGS_SO_libcublasLt.so.12 := -Wl,--version-script=libcublasLt.12.map
LDXXFLAGS_SO_libcublasLt.so.13 := -Wl,--version-script=libcublasLt.13.map
LDXXFLAGS_SO_libcurand.so.10 := -Wl,--version-script=libcurand.map
LDXXFLAGS_SO_libcufft.so.11 := -Wl,--version-script=libcufft.11.map
LDXXFLAGS_SO_libcufft.so.12 := -Wl,--version-script=libcufft.12.map
LDXXFLAGS_SO_libcusparse.so.12 := -Wl,--version-script=libcusparse.map
LDXXFLAGS_SO_libcusolver.so.12 := -Wl,--version-script=libcusolver.12.map
LDXXFLAGS_SO_libnccl.so.2 := -Wl,--version-script=libnccl.map

# ROCm HIP
CXXFLAGS_SO_cuda-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_cuda-module-mgmt-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_blas-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_blasLt-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_fft-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_rand-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_runtime-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_runtime_event-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_runtime_memory-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_runtime_internal-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_solver-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_sparse-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
CXXFLAGS_SO_nccl-hip := ${CXXFLAGS_SO_HIP_SPECIAL}
LDXXFLAGS_SO_libamdhip64.so.5 := -Wl,--version-script=libamdhip64.map
LDXXFLAGS_SO_libamdhip64.so.6 := -Wl,--version-script=libamdhip64.map
LDXXFLAGS_SO_librocfft.so.0 := -Wl,--version-script=librocfft.map
LDXXFLAGS_SO_libhipfft.so.0 := -Wl,--version-script=libhipfft.map
LDXXFLAGS_SO_librocsparse.so.1 := -Wl,--version-script=librocsparse.map
LDXXFLAGS_SO_libhipsparse.so.1 := -Wl,--version-script=libhipsparse.map
LDXXFLAGS_SO_libhiprand.so.1 := -Wl,--version-script=libhiprand.map
LDXXFLAGS_SO_libhipblas.so.2 := -Wl,--version-script=libhipblas.map
LDXXFLAGS_SO_libhipblaslt.so.0 := -Wl,--version-script=libhipblaslt.map
LDXXFLAGS_SO_libhipsolver.so.0 := -Wl,--version-script=libhipsolver.map
LDXXFLAGS_SO_librccl.so.1 := -Wl,--version-script=librccl.map

common-objs := ${OUTPUT}common.cpp.so.o
common-objs += ${OUTPUT}utils.cpp.so.o
common-objs += ${OUTPUT}device.cpp.so.o

rt-objs := ${OUTPUT}runtime.cpp.so.o
rt-objs += ${OUTPUT}runtime_event.cpp.so.o
rt-objs += ${OUTPUT}runtime_memory.cpp.so.o
rt-objs += ${OUTPUT}runtime_internal.cpp.so.o ${OUTPUT}fatbin.cpp.so.o

rt-hpcc-objs := ${OUTPUT}runtime-hpcc.cpp.so.o
rt-hpcc-objs += ${OUTPUT}runtime_event-hpcc.cpp.so.o
rt-hpcc-objs += ${OUTPUT}runtime_memory-hpcc.cpp.so.o
rt-hpcc-objs += ${OUTPUT}runtime_internal-hpcc.cpp.so.o ${OUTPUT}fatbin.cpp.so.o

rt-luca-objs := ${OUTPUT}runtime-luca.cpp.so.o
rt-luca-objs += ${OUTPUT}runtime_event-luca.cpp.so.o
rt-luca-objs += ${OUTPUT}runtime_memory-luca.cpp.so.o
rt-luca-objs += ${OUTPUT}runtime_internal-luca.cpp.so.o ${OUTPUT}fatbin.cpp.so.o

rt-hip-objs := ${OUTPUT}runtime-hip.cpp.so.o
rt-hip-objs += ${OUTPUT}runtime_event-hip.cpp.so.o
rt-hip-objs += ${OUTPUT}runtime_memory-hip.cpp.so.o
rt-hip-objs += ${OUTPUT}runtime_internal-hip.cpp.so.o ${OUTPUT}fatbin.cpp.so.o

${rt-objs}: runtime.hpp
${rt-hpcc-objs}: runtime.hpp
${rt-luca-objs}: runtime.hpp
${rt-hip-objs}: runtime.hpp

${OUTPUT}common.cpp.so.o: debug.h
${OUTPUT}utils.cpp.so.o: utils.hpp
${OUTPUT}fatbin.cpp.so.o: fatbin.hpp fatbin-hip.hpp
${OUTPUT}fft.cpp.so.o: fft.hpp
${OUTPUT}fft-hpcc.cpp.so.o: fft.hpp fft.cpp
${OUTPUT}fft-hip.cpp.so.o: fft.hpp fft.cpp
${OUTPUT}blas.cpp.so.o: blas.hpp
${OUTPUT}blas-hpcc.cpp.so.o: blas.hpp blas.cpp
${OUTPUT}blas-hip.cpp.so.o: blas.hpp blas.cpp
${OUTPUT}blasLt.cpp.so.o: blasLt.hpp
${OUTPUT}blasLt-hpcc.cpp.so.o: blasLt.hpp blasLt.cpp
${OUTPUT}blasLt-hip.cpp.so.o: blasLt.hpp blasLt.cpp
${OUTPUT}sparse.cpp.so.o: sparse.hpp
${OUTPUT}sparse-hpcc.cpp.so.o: sparse.hpp sparse.cpp
${OUTPUT}sparse-hip.cpp.so.o: sparse.hpp sparse.cpp
${OUTPUT}rand.cpp.so.o: rand.hpp
${OUTPUT}rand-hpcc.cpp.so.o: rand.hpp rand.cpp
${OUTPUT}rand-hip.cpp.so.o: rand.hpp rand.cpp
${OUTPUT}nccl-hpcc.cpp.so.o: nccl.hpp
${OUTPUT}cuda.cpp.so.o: cuda.hpp
${OUTPUT}cuda-hpcc.cpp.so.o: cuda.hpp cuda.cpp
${OUTPUT}cuda-hip.cpp.so.o: cuda.hpp cuda.cpp
${OUTPUT}cuda-module-mgmt.cpp.so.o: cuda.hpp
${OUTPUT}cuda-module-mgmt-hpcc.cpp.so.o: cuda.hpp cuda-module-mgmt.cpp
${OUTPUT}cuda-module-mgmt-hip.cpp.so.o: cuda.hpp cuda-module-mgmt.cpp
${OUTPUT}cuda-module-mgmt-hip-private.cpp.so.o: cuda.hpp cuda-module-mgmt.cpp
${OUTPUT}device.cpp.so.o: device.h device-mars-x203.h device-nvidia-h800.h

# HPCC
libhccompiler.so-objs := ${common-objs} ${rt-hpcc-objs}
libhcruntime.so-objs := ${common-objs} ${rt-hpcc-objs} ${OUTPUT}cuda-hpcc.cpp.so.o ${OUTPUT}cuda-module-mgmt-hpcc.cpp.so.o
libhcblas.so-objs := ${common-objs} ${OUTPUT}blas-hpcc.cpp.so.o
libhcblasLt.so-objs := ${common-objs} ${OUTPUT}blasLt-hpcc.cpp.so.o
libhcfft.so-objs := ${common-objs} ${OUTPUT}fft-hpcc.cpp.so.o
libhcrand.so-objs := ${common-objs} ${OUTPUT}rand-hpcc.cpp.so.o
libhcsparse.so-objs := ${common-objs} ${OUTPUT}sparse-hpcc.cpp.so.o
libhcsolver.so-objs := ${common-objs} ${OUTPUT}solver-hpcc.cpp.so.o
libhccl.so-objs := ${common-objs} ${OUTPUT}nccl-hpcc.cpp.so.o

# LUCA
liblccompiler.so-objs := ${common-objs} ${rt-luca-objs}
liblcruntime.so-objs := ${common-objs} ${rt-luca-objs} ${OUTPUT}cuda-luca.cpp.so.o ${OUTPUT}cuda-module-mgmt-luca.cpp.so.o
liblcblas.so-objs := ${common-objs} ${OUTPUT}blas-luca.cpp.so.o
liblcblasLt.so-objs := ${common-objs} ${OUTPUT}blasLt-luca.cpp.so.o
liblcfft.so-objs := ${common-objs} ${OUTPUT}fft-luca.cpp.so.o
liblcrand.so-objs := ${common-objs} ${OUTPUT}rand-luca.cpp.so.o
liblcsparse.so-objs := ${common-objs} ${OUTPUT}sparse-luca.cpp.so.o
liblcsolver.so-objs := ${common-objs} ${OUTPUT}solver-luca.cpp.so.o
liblccl.so-objs := ${common-objs} ${OUTPUT}nccl-luca.cpp.so.o

# CUDA
libcuda.so.1-objs := ${common-objs} ${OUTPUT}cuda.cpp.so.o ${OUTPUT}cuda-module-mgmt.cpp.so.o
libcudart.so.12-objs := ${common-objs} ${rt-objs}
libcudart.so.13-objs := ${common-objs} ${rt-objs}
libcublas.so.12-objs := ${common-objs} ${OUTPUT}blas.cpp.so.o
libcublas.so.13-objs := ${common-objs} ${OUTPUT}blas.cpp.so.o
libcublasLt.so.12-objs := ${common-objs} ${OUTPUT}blasLt.cpp.so.o
libcublasLt.so.13-objs := ${common-objs} ${OUTPUT}blasLt.cpp.so.o
libcusolver.so.12-objs := ${common-objs} ${OUTPUT}solver.cpp.so.o
libcufft.so.11-objs := ${common-objs} ${OUTPUT}fft.cpp.so.o
libcufft.so.12-objs := ${common-objs} ${OUTPUT}fft.cpp.so.o
libcurand.so.10-objs := ${common-objs} ${OUTPUT}rand.cpp.so.o
libcusparse.so.12-objs := ${common-objs} ${OUTPUT}sparse.cpp.so.o
libnccl.so.2-objs := ${common-objs} ${OUTPUT}nccl.cpp.so.o

# ROCm HIP
amdhip64-objs := ${common-objs}
amdhip64-objs += ${rt-hip-objs}
amdhip64-objs += ${OUTPUT}cuda.cpp.so.o
amdhip64-objs += ${OUTPUT}cuda-hip.cpp.so.o
amdhip64-objs += ${OUTPUT}cuda-module-mgmt-hip.cpp.so.o
amdhip64-objs += ${OUTPUT}cuda-module-mgmt-hip-private.cpp.so.o
libamdhip64.so.5-objs := ${amdhip64-objs}
libamdhip64.so.6-objs := ${amdhip64-objs}
librocfft.so.0-objs := ${common-objs} ${OUTPUT}fft-hip.cpp.so.o
libhipfft.so.0-objs := ${common-objs} ${OUTPUT}fft-hip.cpp.so.o
librocsparse.so.1-objs := ${common-objs} ${OUTPUT}sparse-hip.cpp.so.o
libhipsparse.so.1-objs := ${common-objs} ${OUTPUT}sparse-hip.cpp.so.o
libhipsolver.so.0-objs := ${common-objs} ${OUTPUT}solver-hip.cpp.so.o
libhiprand.so.1-objs := ${common-objs} ${OUTPUT}rand-hip.cpp.so.o
libhipblas.so.2-objs := ${common-objs} ${OUTPUT}blas-hip.cpp.so.o
libhipblaslt.so.0-objs := ${common-objs} ${OUTPUT}blasLt-hip.cpp.so.o
librccl.so.1-objs := ${common-objs} ${OUTPUT}nccl-hip.cpp.so.o

include main.mk
