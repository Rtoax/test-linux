#include <stdio.h>
#include <limits.h>
#include <iostream>

class Hello {
	int print(void);
};

int Hello::print(void)
{
	std::cout << "Hello World!" << std::endl;
	return 0;
}

int main(void)
{
	std::cout << "Hello World!" << std::endl;
	return 0;
}
