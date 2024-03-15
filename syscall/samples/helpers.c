#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "helpers.h"


int create_file(const char *filename, char ch, size_t bytes)
{
	int i;
	FILE *fp;

	fp = fopen(filename, "w");
	for (i = 0; i < bytes; i++)
		fwrite(&ch, sizeof(char), 1, fp);
	fclose(fp);

	return 0;
}

