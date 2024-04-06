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

void test2(void)
{
	static void *jump_table[3] = {
		&&label1, &&label2, && label3
	};

	int jmp = -1;

start:
	if (++jmp >= 3)
		return;
	goto *jump_table[jmp];

label1:
	printf("label1.\n");
label2:
	printf("label2.\n");
label3:
	printf("label3.\n");

	goto start;
}

int main(void)
{
	test1();
	test2();
	return 0;
}
