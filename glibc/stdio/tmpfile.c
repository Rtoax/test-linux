#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	FILE *fp = tmpfile();
	fprintf(fp, "Hello, Yue Hua!\n");
	fclose(fp);
	return 0;
}
