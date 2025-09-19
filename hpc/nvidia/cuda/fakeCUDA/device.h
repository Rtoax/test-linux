// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <sys/types.h>


enum devError_t {
	devSuccess,
	devErrorInvalidValue,
};

int devCount(void);
int devMajor(int device);
int devMinor(int device);

int devSetCurrent(int device);
int devGetCurrent(int *device);

long devTotalGlobalMem(int device);
long devTotalConstMem(int device);
long devL2CacheSize(int device);
long devGlobalL1CacheSupported(int device);
long devLocalL1CacheSupported(int device);
long devManagedMemory(int device);
long devMemoryBusWidth(int device);
long devECCEnabled(int device);
long devMultiProcessorCount(int device);
long devMaxThreadsPerMultiProcessor(int device);
long devMaxThreadsPerBlock(int device);
long devMaxThreadsDimx(int device);
long devMaxThreadsDimy(int device);
long devMaxThreadsDimz(int device);
long devMaxGridSizex(int device);
long devMaxGridSizey(int device);
long devMaxGridSizez(int device);
long devClockRate(int device);
long devWarpSize(int device);

int devGetName(int device, char *name, size_t name_len);
