#include <stdio.h>
#include <stdbool.h>

/**
 * dummy变量，直译为“哑元变量”，是在C语言中用于占位、传递参数等目的的变量。它们
 * 通常在函数定义或者调用中用作形式参数，而在实际使用时并不关心这些参数的具体值。
 */
void print_name(const char *name, bool dummy)
{
	if (dummy)
		return;
	printf("%s\n", name);
}

int main(void)
{
	print_name("Rong Tao", false);
	print_name("reserved", true);
	return 0;
}
