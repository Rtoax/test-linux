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
	strcat(string, "1234567890");

	printf("string: %s\n", string);

	/* overflow write to stack_buff[] */
	/**
	 * on aarch64, thinkforce, buf[] and buf_pre[] aligned by 8bytes, thus,
	 * we should match "90".
	 */
	printf("stack_buff: %s\n", stack_buff);
	if (strcmp(stack_buff, "567890") && strcmp(stack_buff, "90")) {
		assert(0 && "stack buffer failed");
	}
}

int main(void)
{
	base();
	overflow();
	return 0;
}
