#pragma once
#include <cuda.h>
#include <cuda_runtime.h>
#include "types.h"

int dev_count(void);

int dev_set_current(int device);
int dev_get_current(int *device);

int dev_get_prop(int device, cudaDeviceProp *prop);
