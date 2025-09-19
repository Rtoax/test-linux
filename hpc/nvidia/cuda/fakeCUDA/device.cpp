// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "device.h"
#include "device-nvidia-h800.h"


#define DEV_COUNT	8

struct device {
	char name[64];
	int id;
	size_t totalGlobalMem;
	size_t totalConstMem;
	size_t l2CacheSize;
	bool globalL1CacheSupported;
	bool localL1CacheSupported;
	bool managedMemory;
	bool ECCEnabled;
	size_t multiProcessorCount;
	size_t maxThreadsPerMultiProcessor;
	size_t maxThreadsPerBlock;
	int maxThreadsDim[3];
	int maxGridSize[3];
	size_t clockRate;
	int warpSize;
	int major, minor;
#define DEV_INITIALIZER(idx)	{	\
		/* error: C99 designator 'name' outside aggregate initializer
		 * .name = { DEV_NAME }, */	\
		.id = idx,	\
		.totalGlobalMem = DEV_TOTAL_GLOBAL_MEM,	\
		.totalConstMem = DEV_TOTAL_CONST_MEM,	\
		.l2CacheSize = DEV_L22CACHESIZE,	\
		.globalL1CacheSupported = DEV_globalL1CacheSupported,	\
		.localL1CacheSupported = DEV_localL1CacheSupported,	\
		.managedMemory = DEV_managedMemory,	\
		.ECCEnabled = DEV_ECCEnabled,	\
		.multiProcessorCount = DEV_multiProcessorCount,	\
		.maxThreadsPerMultiProcessor = DEV_maxThreadsPerMultiProcessor,	\
		.maxThreadsDim = {	\
			DEV_maxThreadsDimX,	\
			DEV_maxThreadsDimY,	\
			DEV_maxThreadsDimZ,	\
		},	\
		.maxGridSize = {	\
			DEV_maxGridSizeX,	\
			DEV_maxGridSizeY,	\
			DEV_maxGridSizeZ,	\
		},	\
		.clockRate = DEV_clockRate,	\
		.warpSize = DEV_warpSize,	\
		.major = DEV_major,	\
		.minor = DEV_minor,	\
	}
};

static pthread_mutex_t mutex_dev = PTHREAD_MUTEX_INITIALIZER;
#define DEV_LOCK()	pthread_mutex_lock(&mutex_dev)
#define DEV_UNLOCK()	pthread_mutex_unlock(&mutex_dev)

static struct device all_devices[DEV_COUNT] = {
	[0] = DEV_INITIALIZER(0),
	[1] = DEV_INITIALIZER(1),
	[2] = DEV_INITIALIZER(2),
	[3] = DEV_INITIALIZER(3),
	[4] = DEV_INITIALIZER(4),
	[5] = DEV_INITIALIZER(5),
	[6] = DEV_INITIALIZER(6),
	[7] = DEV_INITIALIZER(7),
};

static struct device *current_device = NULL;

static void set_default_current_device_lock(void)
{
	DEV_LOCK();
	if (!current_device)
		current_device = &all_devices[0];
	DEV_UNLOCK();
}

int dev_count(void)
{
	return DEV_COUNT;
}

int dev_major(int device)
{
	int major;

	if (device < 0 || device >= DEV_COUNT)
		return devErrorInvalidValue;

	DEV_LOCK();
	major = all_devices[device].major;
	DEV_UNLOCK();

	return major;
}

int dev_minor(int device)
{
	int minor;

	if (device < 0 || device >= DEV_COUNT)
		return devErrorInvalidValue;

	DEV_LOCK();
	minor = all_devices[device].minor;
	DEV_UNLOCK();

	return minor;
}

int dev_set_current(int device)
{
	if (device < 0 || device >= DEV_COUNT)
		return devErrorInvalidValue;

	DEV_LOCK();
	current_device = &all_devices[device];
	DEV_UNLOCK();

	return devSuccess;
}

int dev_get_current(int *device)
{
	set_default_current_device_lock();

	DEV_LOCK();
	*device = current_device->id;
	DEV_UNLOCK();

	return devSuccess;
}

int dev_get_prop(int device, cudaDeviceProp *prop)
{
	if (device < 0 || device >= DEV_COUNT)
		return devErrorInvalidValue;

	set_default_current_device_lock();

	DEV_LOCK();
	strncpy(prop->name, current_device->name, sizeof(prop->name));
#define SET(v)	prop->v = current_device->v;
	SET(totalGlobalMem);
	SET(totalConstMem);
	SET(l2CacheSize);
	SET(globalL1CacheSupported);
	SET(localL1CacheSupported);
	SET(managedMemory);
	//SET(memoryBusWidth);
	SET(ECCEnabled);
	SET(multiProcessorCount);
	SET(maxThreadsPerMultiProcessor);
	SET(maxThreadsPerBlock);
	SET(maxThreadsDim[0]);
	SET(maxThreadsDim[1]);
	SET(maxThreadsDim[2]);
	SET(maxGridSize[0]);
	SET(maxGridSize[1]);
	SET(maxGridSize[2]);
	SET(major);
	SET(minor);
	//SET(clockRate);
	SET(warpSize);
#undef SET
	DEV_UNLOCK();

	return devSuccess;
}

int dev_get_attr(int device, cudaDeviceAttr attr, int *value)
{
	if (device < 0 || device >= DEV_COUNT)
		return devErrorInvalidValue;

	DEV_LOCK();

	switch (attr) {
	case cudaDevAttrEccEnabled:
		*value = all_devices[device].ECCEnabled;
		break;
	case cudaDevAttrManagedMemory:
		*value = all_devices[device].managedMemory;
		break;
	case cudaDevAttrL2CacheSize:
		*value = all_devices[device].l2CacheSize;
		break;
	case cudaDevAttrClockRate:
		*value = all_devices[device].clockRate;
		break;
	case cudaDevAttrMaxThreadsPerBlock:
		*value = all_devices[device].maxThreadsPerBlock;
		break;
	case cudaDevAttrMaxThreadsPerMultiProcessor:
		*value = all_devices[device].maxThreadsPerMultiProcessor;
		break;
	case cudaDevAttrHostNumaId:
		*value = 0;	/* TODO */
		break;
	case cudaDevAttrWarpSize:
		*value = all_devices[device].warpSize;
		break;
	default:
		DEV_UNLOCK();
		return devErrorInvalidValue;
	}

	DEV_UNLOCK();

	return devSuccess;
}
