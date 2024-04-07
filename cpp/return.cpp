#include <stdio.h>
#include <limits.h>
#include <iostream>

int print(void)
{
	std::cout << "Hello World!" << std::endl;
	/* no return */
}

int main(void)
{
	print();
	return 0;
}
