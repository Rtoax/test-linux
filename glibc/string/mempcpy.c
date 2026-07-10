/**
 * void *mempcpy(void dest[n], const void src[n], size_t n);
 */
#include <string.h>
#include <stdio.h>

int main(void)
{
	char buffer[10] = { "123456789" };
	char *to = buffer;

	to = mempcpy(to, "foo", 3);

	puts(to);
	puts(buffer);

	return 0;
}
