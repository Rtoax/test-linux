#include <cuda.h>
#include <cuda_runtime.h>
#include <pthread.h>

#include "device.h"


#define DEV_COUNT	8

struct device {
};

static pthread_mutex_t mutex_dev = PTHREAD_MUTEX_INITIALIZER;
#define DEV_LOCK()	pthread_mutex_lock(&mutex_dev)
#define DEV_UNLOCK()	pthread_mutex_unlock(&mutex_dev)

static struct device all_devices[DEV_COUNT];
static struct device *current_device = NULL;


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
