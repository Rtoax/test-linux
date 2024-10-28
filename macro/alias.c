#include <stdio.h>

#include "alias.h"


void foo(void)
{
	printf("%s\n", __func__);
}

weak_alias(foo, alias1_foo);

void alias2_foo(void) f_weak_alias("foo");


int main(void)
{
	alias1_foo();
	alias2_foo();

	return 0;
}
