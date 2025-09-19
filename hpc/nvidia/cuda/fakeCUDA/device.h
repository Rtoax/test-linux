// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include "compat.hpp"
#include "types.h"

enum devError_t {
	devSuccess,
	devErrorInvalidValue,
};

int devCount(void);
int devMajor(int device);
int devMinor(int device);

int devSetCurrent(int device);
int devGetCurrent(int *device);

int devGetName(int device, char *name, size_t name_len);
int devGetProp(int device, cudaDeviceProp *prop);
int devGetAttr(int device, cudaDeviceAttr attr, int *value);
