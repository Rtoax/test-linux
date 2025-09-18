// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#ifdef HAVE_HPCC
#include <hc_runtime.h>
#include <cuda_adapter.h>
#else
#include <cuda.h>
#include <cuda_runtime.h>
#endif
#include "types.h"

int dev_count(void);
int dev_major(int device);
int dev_minor(int device);

int dev_set_current(int device);
int dev_get_current(int *device);

int dev_get_prop(int device, cudaDeviceProp *prop);
int dev_get_attr(int device, cudaDeviceAttr attr, int *value);
