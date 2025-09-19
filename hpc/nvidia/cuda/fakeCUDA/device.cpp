// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "debug.h"
#include "utils.hpp"
#include "device.h"
#include "device-nvidia-h800.h"
#include "device-mars-x203.h"


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
	size_t memoryBusWidth;
	size_t multiProcessorCount;
	size_t maxThreadsPerMultiProcessor;
	size_t maxThreadsPerBlock;
	int maxThreadsDim[3];
	int maxGridSize[3];
	size_t clockRate;
	int warpSize;
	int major, minor;
};

static pthread_mutex_t mutex_dev = PTHREAD_MUTEX_INITIALIZER;
#define DEV_LOCK()	pthread_mutex_lock(&mutex_dev)
#define DEV_UNLOCK()	pthread_mutex_unlock(&mutex_dev)

static struct device all_devices[] = {
	[0] = DEV_NVIDIA_H800_INITIALIZER(0),
	[1] = DEV_NVIDIA_H800_INITIALIZER(1),
	[2] = DEV_NVIDIA_H800_INITIALIZER(2),
	[3] = DEV_NVIDIA_H800_INITIALIZER(3),
	[4] = DEV_NVIDIA_H800_INITIALIZER(4),
	[5] = DEV_NVIDIA_H800_INITIALIZER(5),
	[6] = DEV_NVIDIA_H800_INITIALIZER(6),
	[7] = DEV_NVIDIA_H800_INITIALIZER(7),
	[8] = DEV_MARS_X203_INITIALIZER(8),
	[9] = DEV_MARS_X203_INITIALIZER(9),
	[10] = DEV_MARS_X203_INITIALIZER(10),
	[11] = DEV_MARS_X203_INITIALIZER(11),
	[12] = DEV_MARS_X203_INITIALIZER(12),
	[13] = DEV_MARS_X203_INITIALIZER(13),
	[14] = DEV_MARS_X203_INITIALIZER(14),
	[15] = DEV_MARS_X203_INITIALIZER(15),
};

static struct device *current_device = NULL;

#define CHECK_DEV(device)	\
	if (device < 0 || device >= ARRAY_SIZE(all_devices)) {	\
		fprintf(stderr, "ERROR: bad device id %d\n", device);	\
		return devErrorInvalidValue;	\
	}	\
	set_default_current_device_lock();	\
	struct device *_____dev = &all_devices[device];
#define DEVICE	_____dev


static void set_default_current_device_lock(void)
{
	DEV_LOCK();
	if (!current_device)
		current_device = &all_devices[0];
	DEV_UNLOCK();
}

int devCount(void)
{
	return ARRAY_SIZE(all_devices);
}

int devMajor(int device)
{
	int major;

	CHECK_DEV(device);

	DEV_LOCK();
	major = all_devices[device].major;
	DEV_UNLOCK();

	return major;
}

int devMinor(int device)
{
	int minor;

	CHECK_DEV(device);

	DEV_LOCK();
	minor = all_devices[device].minor;
	DEV_UNLOCK();

	return minor;
}

int devSetCurrent(int device)
{
	CHECK_DEV(device);

	DEV_LOCK();
	current_device = &all_devices[device];
	DEV_UNLOCK();

	return devSuccess;
}

int devGetCurrent(int *device)
{
	set_default_current_device_lock();

	DEV_LOCK();
	*device = current_device->id;
	DEV_UNLOCK();

	return devSuccess;
}

int devGetName(int device, char *name, size_t name_len)
{
	CHECK_DEV(device);
	strncpy(name, DEVICE->name, name_len);
	DEBUG_DBG("name = %s\n", name);
	return devSuccess;
}

long devTotalGlobalMem(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->totalGlobalMem;
	DEV_UNLOCK();
	return ret;
}

long devTotalConstMem(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->totalConstMem;
	DEV_UNLOCK();
	return ret;
}

long devL2CacheSize(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->l2CacheSize;
	DEV_UNLOCK();
	return ret;
}

long devGlobalL1CacheSupported(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->globalL1CacheSupported;
	DEV_UNLOCK();
	return ret;
}

long devLocalL1CacheSupported(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->localL1CacheSupported;
	DEV_UNLOCK();
	return ret;
}

long devManagedMemory(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->managedMemory;
	DEV_UNLOCK();
	return ret;
}

long devMemoryBusWidth(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->memoryBusWidth;
	DEV_UNLOCK();
	return ret;
}

long devECCEnabled(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->ECCEnabled;
	DEV_UNLOCK();
	return ret;
}

long devMultiProcessorCount(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->multiProcessorCount;
	DEV_UNLOCK();
	return ret;
}

long devMaxThreadsPerMultiProcessor(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxThreadsPerMultiProcessor;
	DEV_UNLOCK();
	return ret;
}

long devMaxThreadsPerBlock(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxThreadsPerBlock;
	DEV_UNLOCK();
	return ret;
}

long devMaxThreadsDimx(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxThreadsDim[0];
	DEV_UNLOCK();
	return ret;
}

long devMaxThreadsDimy(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxThreadsDim[1];
	DEV_UNLOCK();
	return ret;
}

long devMaxThreadsDimz(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxThreadsDim[2];
	DEV_UNLOCK();
	return ret;
}

long devMaxGridSizex(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxGridSize[0];
	DEV_UNLOCK();
	return ret;
}

long devMaxGridSizey(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxGridSize[1];
	DEV_UNLOCK();
	return ret;
}

long devMaxGridSizez(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->maxGridSize[2];
	DEV_UNLOCK();
	return ret;
}

long devClockRate(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->clockRate;
	DEV_UNLOCK();
	return ret;
}

long devWarpSize(int device)
{
	CHECK_DEV(device);
	DEV_LOCK();
	long ret = DEVICE->warpSize;
	DEV_UNLOCK();
	return ret;
}
