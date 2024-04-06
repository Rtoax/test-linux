#include <stdio.h>

void test1(void)
{
	void *ptr;
	int times = 0;

	ptr = &&foo;
foo:
	printf("%p\n", ptr);

	if (times++ < 4)
		goto *ptr;
}

int main(void)
{
	test1();
	return 0;
}
