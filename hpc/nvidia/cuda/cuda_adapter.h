// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_H
#define __CUDA_ADAPTER_H 1

#define CUDA_ADAPTER_MAJOR 1
#define CUDA_ADAPTER_MINOR 3
#define CUDA_ADAPTER_PATCH 0

#include "adapter/cuda.h"
#include "adapter/cuda_runtime.h"
#include "adapter/cuda_runtime_api.h"
#include "adapter/driver_types.h"

#include "adapter/cuComplex.h"
#include "adapter/cublas.h"
#include "adapter/cublasLt.h"
#include "adapter/curand.h"
#include "adapter/cufft.h"
#include "adapter/cusparse.h"

#include "adapter/nvrtc.h"

#include "adapter/device_types.h"
#include "adapter/cuda_fp6.h"
#include "adapter/cuda_fp8.h"
#include "adapter/cuda_bf16.h"

#include "adapter/cudnn.h"
#include "adapter/cusolver.h"
#include "adapter/cufile.h"
#include "adapter/cupti.h"
#include "adapter/nccl.h"

#endif
