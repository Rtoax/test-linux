#include <format>
#include <iostream>

std::string format(void)
{
	return std::format("$${}_{}", "Hello", "World");
}

int main(void)
{
	std::cout << format() << std::endl;
	return 0;
}
