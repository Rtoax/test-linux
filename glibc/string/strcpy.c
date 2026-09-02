/**
 * char *strcpy(char *dst, const char *src);
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>

void base(void)
{
	char buf[5];

	strcpy(buf, "1234");
	printf("buf: %s\n", buf);
}

void overflow(void)
{
	char buf_pre[32] = { 0 };
	char buf[4];

	strcpy(buf, "1234567890");

	printf("buf: %s\n", buf);
	printf("buf_pre: %s\n", buf_pre);

	/* overflow write to buf_pre[] */
	/**
	 * on aarch64, thinkforce, buf[] and buf_pre[] aligned by 8bytes, thus,
	 * we should match "90".
	 */
	if (strcmp(buf_pre, "567890") && strcmp(buf_pre, "90")) {
		assert(0 && "pre buffer failed");
	}
}

int main(void)
{
	base();
	overflow();
	return 0;
}
