#include <malloc.h>
#include <string.h>

int main(void)
{
	char *a = (char *)malloc(10);
	char *b = (char *)malloc(10);

	(void)b;

	/* Buffer overflow corrupts 'b's metadata */
	/* Writes 20 bytes into a 10-byte buffer */
	memset(a, 0, 20);
	/* May trigger error when 'b' is freed later */
	free(a);

	return 0;
}
