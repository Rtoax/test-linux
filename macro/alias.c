#include <stdio.h>

#include "alias.h"


void __func1(void)
{
	printf("%s\n", __func__);
}
weak_alias(__func1, alias1_func1);

void alias2_func1(void) f_weak_alias("__func1");


int main(void)
{
	alias1_func1();
	alias2_func1();

	return 0;
}
