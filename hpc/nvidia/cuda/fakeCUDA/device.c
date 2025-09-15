#include <cuda.h>
#include <cuda_runtime.h>
#include <pthread.h>

#include "device.h"


#define DEV_COUNT	8

struct device {
	int id;
};

static pthread_mutex_t mutex_dev = PTHREAD_MUTEX_INITIALIZER;
#define DEV_LOCK()	pthread_mutex_lock(&mutex_dev)
#define DEV_UNLOCK()	pthread_mutex_unlock(&mutex_dev)

static struct device all_devices[DEV_COUNT] = {
	[0] = { .id = 0, },
	[1] = { .id = 1, },
	[2] = { .id = 2, },
	[3] = { .id = 3, },
	[4] = { .id = 4, },
	[5] = { .id = 5, },
	[6] = { .id = 6, },
	[7] = { .id = 7, },
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
