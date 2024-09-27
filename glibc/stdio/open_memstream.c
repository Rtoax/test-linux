#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#if defined(M32)
# define PRId   PRId32
#else
# define PRId   PRId64
#endif


int main(void)
{
	char *bp;
	size_t size;
	FILE *stream;

	stream = open_memstream(&bp, &size);
	fprintf(stream, "hello");
	fflush(stream);

	printf("buf = '%s', size = %" PRId "\n", bp, size);

	fprintf(stream, ", world");
	fclose(stream);

	printf("buf = '%s', size = %" PRId "\n", bp, size);

	free(bp);
	return 0;
}
