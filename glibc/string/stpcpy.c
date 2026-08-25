/**
 * char *stpcpy(char *dst, const char *src);
 */
#include <string.h>
#include <stdio.h>

int main(void)
{
	char buffer[10] = { "123456789" };
	char *to = buffer;

	to = stpcpy(to, "foo");
	to = stpcpy(to, "bar");
	to = stpcpy(to, "1");

	puts(to);
	puts(buffer);

	return 0;
}
