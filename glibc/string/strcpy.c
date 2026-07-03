#include <assert.h>
#include <string.h>
#include <stdio.h>

void base(void)
{
	char buf[5];

	strcpy(buf, "1234");
	printf("%s\n", buf);
}

void overflow(void)
{
	char buf_pre[32] = { 0 };
	char buf[4];

	strcpy(buf, "12345678");

	printf("%s\n", buf);
	printf("%s\n", buf_pre);

	/* overflow write to buf_pre[] */
	assert(!strcmp(buf_pre, "5678"));
}

int main(void)
{
	base();
	overflow();
	return 0;
}
