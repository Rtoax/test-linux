#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dlfcn.h>
#include <errno.h>

#include "libdev.h"


#define ORIG_LIBDEV	"libdev.so.1"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


struct symbol {
	const char *name;
	void *ptr;
};

static struct symbol libdev_table[] = {
	{
		.name = "dev_malloc",
		.ptr = NULL,
	},
	{
		.name = "dev_gettotalmemsize",
		.ptr = NULL,
	},
	{
		.name = "dev_getallocatedsize",
		.ptr = NULL,
	},
};

static int dev_memsize = 0;
static int dev_memuse = 0;

static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static pthread_rwlock_t dev_rwlock;


static inline void *find_fptr(const char *name)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(libdev_table); i++) {
		if (!strcmp(name, libdev_table[i].name))
			return libdev_table[i].ptr;
	}
	return NULL;
}

static void init_libdev(void)
{
	int i;
	void *handle;

	pthread_rwlock_init(&dev_rwlock, NULL);

	handle = dlopen(ORIG_LIBDEV, RTLD_NOW | RTLD_NODELETE);

	for (i = 0; i < ARRAY_SIZE(libdev_table); i++) {
		libdev_table[i].ptr = dlsym(handle, libdev_table[i].name);
	}

	dlclose(handle);

	int (*getsize)(void) = find_fptr("dev_gettotalmemsize");
	pthread_rwlock_wrlock(&dev_rwlock);
	/* Only give user 50% memory. */
	dev_memsize = getsize() / 2;
	dev_memuse = 0;
	pthread_rwlock_unlock(&dev_rwlock);
}

static int hacking_init(void)
{
	pthread_once(&init_once, init_libdev);
	return 0;
}

char *dev_malloc(size_t size)
{
	hacking_init();
	char *new = NULL;

	int (*getsize)(void) = find_fptr("dev_getallocatedsize");
	char *(*orig)(size_t) = find_fptr("dev_malloc");

	if (!getsize || !orig) {
		fprintf(stderr, "Not found APIs.\n");
		errno = -EINVAL;
		return NULL;
	}

	pthread_rwlock_rdlock(&dev_rwlock);
	if (dev_memuse + size > dev_memsize) {
		fprintf(stderr, "Device out of memory.\n");
		errno = -ENOMEM;
		pthread_rwlock_unlock(&dev_rwlock);
		return NULL;
	}

	new = orig(size);
	if (new)
		dev_memuse += size;

	pthread_rwlock_unlock(&dev_rwlock);

	return new;
}

int dev_gettotalmemsize(void)
{
	hacking_init();
	int total = 0;
	pthread_rwlock_rdlock(&dev_rwlock);
	total = dev_memsize;
	pthread_rwlock_unlock(&dev_rwlock);
	return total;
}

int dev_getallocatedsize(void)
{
	hacking_init();
	int use = 0;
	pthread_rwlock_rdlock(&dev_rwlock);
	use = dev_memuse;
	pthread_rwlock_unlock(&dev_rwlock);
	return use;
}
