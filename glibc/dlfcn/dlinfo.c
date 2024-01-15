#include <stdio.h>
#define __USE_GNU
#include <link.h>
#include <dlfcn.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <libs/proc.h>
#include "common.h"


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
	printf("%16s : addr : %lx\n", lib, linkmap->l_addr);
	printf("%16s : name : %s\n", lib, linkmap->l_name);

	dlclose(handle);
}

int main(void)
{
	print_proc_pid_maps();
	test("libc.so.6");
	test("ld-linux-x86-64.so.2");
	print_proc_pid_maps();
	return 0;
}

