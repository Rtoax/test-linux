#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

static int one(const struct dirent *unused)
{
	return 1;
}

int tl_collsort(const struct dirent **d1, const struct dirent **d2)
{
	return strcoll(d1[0]->d_name, d2[0]->d_name);
}

int tl_versort(const struct dirent **d1, const struct dirent **d2)
{
	return strverscmp(d1[0]->d_name, d2[0]->d_name);
}

int test(void *filter, void *compar)
{
	struct dirent **namelist;

	int n = scandir("./", &namelist, filter, compar);
	if (n < 0) {
		perror("scandir.");
		exit(1);
	}
	while (n--) {
		printf("%s\n", namelist[n]->d_name);
		free(namelist[n]);
	}
	free(namelist);

	return 0;
}

int main(void)
{
	test(NULL, alphasort);
	test(NULL, versionsort);
	test(one, tl_collsort);
	test(one, tl_versort);
	return 0;
}
