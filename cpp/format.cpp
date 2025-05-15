#ifdef __has_include
# if __has_include (<format>)
#include <format>
# endif
#endif
#include <iostream>

#if __cplusplus < 202002L
#error "only -std >= c++20 support std::format"
#endif

std::string format(void)
{
	return std::format("$${}_{}", "Hello", "World");
}

int main(void)
{
	std::cout << format() << std::endl;
	return 0;
}
