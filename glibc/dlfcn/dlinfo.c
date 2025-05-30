#include <stdio.h>
#define __USE_GNU
#include <link.h>
#include <dlfcn.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

#include "proc_helpers.h"
#include "common.h"

#if defined(M32)
# define PRI   PRIx32
#else
# define PRI   PRIx64
#endif

static void test(const char *lib)
{
	void *handle;
	struct link_map *linkmap;

	handle = dlopen(lib, RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	if (!handle) {
		perror("dlopen");
		return;
	}

	/* Obtain a pointer to the link_map structure corresponding to handle. */
	dlinfo(handle, RTLD_DI_LINKMAP, &linkmap);
	printf("%16s : addr : %" PRI "\n", lib, linkmap->l_addr);
	printf("%16s : name : %s\n", lib, linkmap->l_name);

	dlclose(handle);
}

int main(int argc, char *argv[])
{
	proc_pid_maps_display();
	test("libc.so.6");
	test("ld-linux-x86-64.so.2");
	proc_pid_maps_display();
	return 0;
}

