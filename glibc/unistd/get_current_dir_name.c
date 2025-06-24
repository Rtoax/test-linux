#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


char *gnu_getcwd(void)
{
	return get_current_dir_name();
}

int main(void)
{
	printf("%s\n", get_current_dir_name());
	return 0;
}
