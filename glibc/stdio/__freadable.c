#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>


int main(void)
{
	FILE *fp1 = fopen("rongtao.out", "w");

	printf("readable:%d\n", __freadable(fp1));
	printf("writable:%d\n", __fwritable(fp1));
	printf("reading:%d\n", __freading(fp1));
	printf("writing:%d\n", __fwriting(fp1));

	__fsetlocking(fp1, 1);

	fclose(fp1);
	return 0;
}
