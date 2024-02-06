#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char *bp;
	size_t size;
	FILE *stream;

	stream = open_memstream(&bp, &size);
	fprintf(stream, "hello");
	fflush(stream);

	printf("buf = '%s', size = %ld\n", bp, size);

	fprintf(stream, ", world");
	fclose(stream);

	printf("buf = '%s', size = %ld\n", bp, size);

	free(bp);
	return 0;
}
