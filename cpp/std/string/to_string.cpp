#include <iostream>

int main(void)
{
	std::string rst = std::string("hello") + std::to_string(3.14) +
			  std::string("world");
	std::cout << rst << std::endl;
	return 0;
}
