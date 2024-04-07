#include <stdio.h>

int func(void)
{
	__asm__("int3");
}

int main(void)
{
	int i = 0;
	while (i < 6){
		printf("i : %d\n", i);
		__asm__("int3");
		++i;
		func();
	}
}
