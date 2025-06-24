#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *id, *ret;

	id = getlogin();
	printf("userid = %s\n", id);

	getlogin_r(id, 10);
	printf("userid = %s\n", id);

	ret = cuserid(id);
	printf("id = %s\n", id);
	printf("ret = %s\n", ret);

	return 0;
}

