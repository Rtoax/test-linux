#pragma once

#if defined(__HPCC__) || defined(__NVCC__) || defined(__HIPCC__)
# define HAVE_CUDA	1
# if defined(__HPCC__)	/* MetaX */
#  include <hccl.h>
#  include <hpcc_fp16.h>
#  include <hpcc_bfloat16.h>
#  include <hc_runtime.h>
#  include "cuda_adapter.h"
# elif defined(__NVCC__)	/* Nvidia */
#  include <cuda_fp16.h>
#  include <cuda_bf16.h>
#  include <cuda_runtime.h>
# elif defined(__HIPCC__)	/* AMD ROCm HIP */
#  include <hip/hip_runtime.h>
#  include <hip/hip_bf16.h>
#  include <hip/hip_fp16.h>
#  include "cuda_adapter.h"
# endif
#endif
