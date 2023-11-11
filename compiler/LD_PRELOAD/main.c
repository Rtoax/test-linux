#include <stdio.h>

int func2(void)
{
	return 'R';
}

int func1(void)
{
	return func2();
}

int main(int argc, char *argv[])
{
	func1();
	return 0;
}
