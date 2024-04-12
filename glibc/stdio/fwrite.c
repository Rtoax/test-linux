#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
	FILE *fp;
	float f = 1.0;

	fp = fopen("tmp.bin", "wb");
	for (i = 0; i < 200; i++)
		fwrite(&f, 1, 4L, fp);
	fclose(fp);

	return 1;
}
