/**
 * char *strcat(char *dst, const char *src);
 * char *strncat(char *dst, const char src[.ssize], size_t ssize);
 *
 * String concatenate/catenate.
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

void base(void)
{
	char string[16] = { 0 };

	printf("%s\n", string);
	strcat(string, "rong");
	printf("%s\n", string);

	strcat(string, " tao");
	printf("%s\n", string);

	strncat(string, " nihaoXXXXXXX", 6);
	printf("%s\n", string);
}

void overflow(void)
{
	char stack_buff[32] = { 0 };
	char string[4] = { 0 };

	/**
	 * need cflags -Wno-error=stringop-overflow
	 */
	strcat(string, "12345678");

	printf("%s\n", string);

	/* overflow write to stack_buff[] */
	printf("%s\n", stack_buff);
	assert(!strcmp(stack_buff, "5678"));
}

int main(void)
{
	base();
	overflow();
	return 0;
}
