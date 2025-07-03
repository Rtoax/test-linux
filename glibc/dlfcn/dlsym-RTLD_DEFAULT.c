#define _GNU_SOURCE 1
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>


int main(void)
{
	int (*p1)(const char *restrict format, ...);

	p1 = dlsym(RTLD_DEFAULT, "printf");
	if (p1 == NULL) {
		printf("%s\n", dlerror());
		exit(1);
	}

	p1("Hello, %s\n", "World");

	return 0;
}
