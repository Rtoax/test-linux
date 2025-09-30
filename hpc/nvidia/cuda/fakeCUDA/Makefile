# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

sub-dir := frontend

include ../cuda.mk
include ../../../metax/hpcc.mk
include ../../../amd/rocm/rocm.mk

libso-hpcc := libhccompiler.so
libso-hpcc += libhccl.so
libso-hpcc += libhcruntime.so
libso-hpcc += libhcblas.so
libso-hpcc += libhcblasLt.so
libso-hpcc += libhcfft.so
libso-hpcc += libhcrand.so
libso-hpcc += libhcsparse.so

libso-cuda := libcuda.so.1
libso-cuda += libcudart.so.12 libcudart.so.13
libso-cuda += libcublas.so.12 libcublas.so.13
libso-cuda += libcublasLt.so.12 libcublasLt.so.13
libso-cuda += libcufft.so.11 libcufft.so.12
libso-cuda += libcurand.so.10
libso-cuda += libcusparse.so.12

libso-hip := libamdhip64.so.5 libamdhip64.so.6
libso-hip += libhipfft.so.0 librocfft.so.0
libso-hip += libhipsparse.so.1 librocsparse.so.1
libso-hip += libhiprand.so.1
libso-hip += libhipblas.so.2 libhipblaslt.so.0

ifdef HAVE_HPCC
  $(info HAVE_HPCC=1)
  targets-libso-cpp += ${libso-hpcc}

  CXXFLAGS_SO += -I${HPCC_ROOT}/include/
  CXXFLAGS_SO += -I${HPCC_ROOT}/include/common/
  CXXFLAGS_SO += -I${HPCC_ROOT}/include/hcr/
  CXXFLAGS_SO += -I${HPCC_ROOT}/include/hcsparse/

  CXXFLAGS_SO += -DHAVE_HPCC=1
endif

ifdef HAVE_CUDA
  $(info HAVE_CUDA)
  targets-libso-cpp += ${libso-cuda}

  CXXFLAGS_SO += -I/usr/local/cuda/include/
  CXXFLAGS_SO += -DCUDA_VERSION_MAJOR=${CUDA_VERSION_MAJOR}
  CXXFLAGS_SO += -DCUDA_VERSION_MINOR=${CUDA_VERSION_MINOR}
  CXXFLAGS_SO += -DCUDA_VERSION_PATCH=${CUDA_VERSION_PATCH}

  CXXFLAGS_SO += -DHAVE_CUDA=1
endif

ifdef HAVE_HIP
  $(info HAVE_HIP)
  targets-libso-cpp += ${libso-hip}

  CXXFLAGS_SO += -I.
  CXXFLAGS_SO += -DHAVE_HIP=1
endif

# HPCC
LDXXFLAGS_SO_libhccompiler.so := -Wl,--version-script=libhccompiler.map
LDXXFLAGS_SO_libhccl.so := -Wl,--version-script=libhccl.map
LDXXFLAGS_SO_libhcruntime.so := -Wl,--version-script=libhcruntime.map
LDXXFLAGS_SO_libhcblas.so := -Wl,--version-script=libhcblas.map
LDXXFLAGS_SO_libhcblasLt.so := -Wl,--version-script=libhcblasLt.map
LDXXFLAGS_SO_libhcfft.so := -Wl,--version-script=libhcfft.map
LDXXFLAGS_SO_libhcrand.so := -Wl,--version-script=libhcrand.map
LDXXFLAGS_SO_libhcsparse.so := -Wl,--version-script=libhcsparse.map

# CUDA
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

# ROCm HIP
LDXXFLAGS_SO_libamdhip64.so.5 := -Wl,--version-script=libamdhip64.map
LDXXFLAGS_SO_libamdhip64.so.6 := -Wl,--version-script=libamdhip64.map
LDXXFLAGS_SO_librocfft.so.0 := -Wl,--version-script=librocfft.map
LDXXFLAGS_SO_libhipfft.so.0 := -Wl,--version-script=libhipfft.map
LDXXFLAGS_SO_librocsparse.so.1 := -Wl,--version-script=librocsparse.map
LDXXFLAGS_SO_libhipsparse.so.1 := -Wl,--version-script=libhipsparse.map
LDXXFLAGS_SO_libhiprand.so.1 := -Wl,--version-script=libhiprand.map
LDXXFLAGS_SO_libhipblas.so.2 := -Wl,--version-script=libhipblas.map
LDXXFLAGS_SO_libhipblaslt.so.0 := -Wl,--version-script=libhipblaslt.map

include ../../../../template/main.mk

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

rt-hip-objs := ${OUTPUT}runtime-hip.cpp.so.o
rt-hip-objs += ${OUTPUT}runtime_event-hip.cpp.so.o
rt-hip-objs += ${OUTPUT}runtime_memory-hip.cpp.so.o
rt-hip-objs += ${OUTPUT}runtime_internal-hip.cpp.so.o ${OUTPUT}fatbin.cpp.so.o

${rt-objs}: runtime.hpp
${rt-hpcc-objs}: runtime.hpp cuda_compat.h
${rt-hip-objs}: runtime.hpp cuda_compat.h

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
${OUTPUT}hccl.cpp.so.o: hccl.hpp
${OUTPUT}cuda.cpp.so.o: cuda.hpp
${OUTPUT}cuda-hpcc.cpp.so.o: cuda.hpp cuda.cpp
${OUTPUT}cuda-hip.cpp.so.o: cuda.hpp cuda.cpp
${OUTPUT}cuda-module-mgmt.cpp.so.o: cuda.hpp
${OUTPUT}cuda-module-mgmt-hpcc.cpp.so.o: cuda.hpp cuda-module-mgmt.cpp
${OUTPUT}cuda-module-mgmt-hip.cpp.so.o: cuda.hpp cuda-module-mgmt.cpp
${OUTPUT}cuda-module-mgmt-hip-private.cpp.so.o: cuda.hpp cuda-module-mgmt.cpp
${OUTPUT}device.cpp.so.o: device.h device-mars-x203.h device-nvidia-h800.h

# HPCC
libhccompiler.so: ${common-objs} ${rt-hpcc-objs}
libhccl.so: ${common-objs} ${OUTPUT}hccl.cpp.so.o
libhcruntime.so: ${common-objs} ${rt-hpcc-objs} ${OUTPUT}cuda-hpcc.cpp.so.o ${OUTPUT}cuda-module-mgmt-hpcc.cpp.so.o
libhcblas.so: ${common-objs} ${OUTPUT}blas-hpcc.cpp.so.o
libhcblasLt.so: ${common-objs} ${OUTPUT}blasLt-hpcc.cpp.so.o
libhcfft.so: ${common-objs} ${OUTPUT}fft-hpcc.cpp.so.o
libhcrand.so: ${common-objs} ${OUTPUT}rand-hpcc.cpp.so.o
libhcsparse.so: ${common-objs} ${OUTPUT}sparse-hpcc.cpp.so.o

# CUDA
libcuda.so.1: ${common-objs} ${OUTPUT}cuda.cpp.so.o ${OUTPUT}cuda-module-mgmt.cpp.so.o
libcudart.so.12: ${common-objs} ${rt-objs}
libcudart.so.13: ${common-objs} ${rt-objs}
libcublas.so.12: ${common-objs} ${OUTPUT}blas.cpp.so.o
libcublas.so.13: ${common-objs} ${OUTPUT}blas.cpp.so.o
libcublasLt.so.12: ${common-objs} ${OUTPUT}blasLt.cpp.so.o
libcublasLt.so.13: ${common-objs} ${OUTPUT}blasLt.cpp.so.o
libcufft.so.11: ${common-objs} ${OUTPUT}fft.cpp.so.o
libcufft.so.12: ${common-objs} ${OUTPUT}fft.cpp.so.o
libcurand.so.10: ${common-objs} ${OUTPUT}rand.cpp.so.o
libcusparse.so.12: ${common-objs} ${OUTPUT}sparse.cpp.so.o

# ROCm HIP
amdhip64-objs := ${common-objs}
amdhip64-objs += ${rt-hip-objs}
amdhip64-objs += ${OUTPUT}cuda.cpp.so.o
amdhip64-objs += ${OUTPUT}cuda-hip.cpp.so.o
amdhip64-objs += ${OUTPUT}cuda-module-mgmt-hip.cpp.so.o
amdhip64-objs += ${OUTPUT}cuda-module-mgmt-hip-private.cpp.so.o
libamdhip64.so.5: ${amdhip64-objs}
libamdhip64.so.6: ${amdhip64-objs}
librocfft.so.0: ${common-objs} ${OUTPUT}fft-hip.cpp.so.o
libhipfft.so.0: ${common-objs} ${OUTPUT}fft-hip.cpp.so.o
librocsparse.so.1: ${common-objs} ${OUTPUT}sparse-hip.cpp.so.o
libhipsparse.so.1: ${common-objs} ${OUTPUT}sparse-hip.cpp.so.o
libhiprand.so.1: ${common-objs} ${OUTPUT}rand-hip.cpp.so.o
libhipblas.so.2: ${common-objs} ${OUTPUT}blas-hip.cpp.so.o
libhipblaslt.so.0: ${common-objs} ${OUTPUT}blasLt-hip.cpp.so.o
