#include <stdio.h>
#include <malloc.h>


int main(void)
{
	FILE *fp = fopen("malloc_info.xml", "w");
	char *p1 = malloc(1039);

	malloc_info(0, stderr);
	malloc_info(0, fp);

	free(p1);
	fclose(fp);
}

