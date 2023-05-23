#include <stdio.h>
#include "alias.h"

void __func1(void)
{
	printf("%s\n", __func__);
}

void func1(void) weak_alias("__func1");

int main(void)
{
	func1();

	return 0;
}
