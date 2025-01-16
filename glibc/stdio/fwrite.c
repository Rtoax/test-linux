#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i;
	FILE *fp;
	const uint8_t u8 = 0xff;
	const int pagesz = getpagesize();

	fp = fopen("tmp.bin", "wb");
	for (i = 0; i < pagesz; i++)
		fwrite(&u8, sizeof(u8), 1, fp);
	fclose(fp);

	return 1;
}
