#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dlfcn.h>

#include "libdev.h"


#define ORIG_LIBDEV	"libdev.so.1"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


struct symbol {
	const char *name;
	void *ptr;
};

static struct symbol libdev_table[] = {
	{
		.name = "dev_gettotalmemsize",
		.ptr = NULL,
	},
};

static pthread_once_t init_once = PTHREAD_ONCE_INIT;


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

	handle = dlopen(ORIG_LIBDEV, RTLD_NOW | RTLD_NODELETE);

	for (i = 0; i < ARRAY_SIZE(libdev_table); i++) {
		libdev_table[i].ptr = dlsym(handle, libdev_table[i].name);
	}

	dlclose(handle);
}

static int hacking_init(void)
{
	pthread_once(&init_once, init_libdev);
	return 0;
}

int dev_gettotalmemsize(void)
{
	hacking_init();
	int (*orig)(void) = find_fptr("dev_gettotalmemsize");
	/**
	 * Only give user 50% memory.
	 */
	if (orig)
		return orig() / 2;
	/* fake value */
	return 64;
}

