#include <cuda.h>
#include <cuda_runtime.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "device.h"


#define DEV_COUNT	8
#define DEV_NAME	"NVIDIA H800"
#define DEV_TOTAL_GLOBAL_MEM	8321499136	/* 8GiB */
#define DEV_TOTAL_CONST_MEM	65536
#define DEV_L22CACHESIZE	52428800
#define DEV_globalL1CacheSupported	1
#define DEV_localL1CacheSupported	1
#define DEV_managedMemory	1
#define DEV_ECCEnabled	1
#define DEV_multiProcessorCount	132
#define DEV_maxThreadsPerMultiProcessor	2048
#define DEV_maxThreadsPerBlock	1024
#define DEV_maxThreadsDimX	1024
#define DEV_maxThreadsDimY	1024
#define DEV_maxThreadsDimZ	64
#define DEV_maxGridSizeX	2147483647
#define DEV_maxGridSizeY	65535
#define DEV_maxGridSizeZ	65535
#define DEV_clockRate	1980000
#define DEV_warpSize	32
#define DEV_major	9
#define DEV_minor	0

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
		.name = DEV_NAME,	\
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

int dev_set_current(int device)
{
	if (device < 0 || device >= DEV_COUNT)
		return cudaErrorInvalidValue;

	DEV_LOCK();
	current_device = &all_devices[device];
	DEV_UNLOCK();

	return cudaSuccess;
}

int dev_get_current(int *device)
{
	set_default_current_device_lock();

	DEV_LOCK();
	*device = current_device->id;
	DEV_UNLOCK();

	return cudaSuccess;
}

int dev_get_prop(int device, cudaDeviceProp *prop)
{
	if (device < 0 || device >= DEV_COUNT)
		return cudaErrorInvalidValue;

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

	return cudaSuccess;
}
