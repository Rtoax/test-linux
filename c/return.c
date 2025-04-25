#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


void func1(void)
{
}

void func2(void)
{
	return;
}

int func3(void)
{
	return true;
}

int func4(int i)
{
	return false;
}

int main(void)
{
	while (1) {
		printf("func3 return %d\n", func3());
		printf("func4 return %d\n", func4(0));
		sleep(1);
	}
	return 0;
}
