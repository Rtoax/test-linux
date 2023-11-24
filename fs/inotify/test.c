#include <stdio.h>
#include <assert.h>


int main(void)
{
	char *filename = "test.txt";
	char buffer[1024];

	/* create it first */
	FILE *fp = fopen(filename, "w+");
	fclose(fp);

	fp = fopen(filename, "rw+");
	assert(fp && "fopen failed");
	fprintf(fp, "Hello\n");

	fscanf(fp, "%s\n", buffer);

	fclose(fp);
	return 0;
}
