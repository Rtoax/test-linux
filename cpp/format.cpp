#ifdef __has_include
# if __has_include (<format>)
#  ifdef ERROR
#    error "std::format is banned. Use fmt::format instead."
#  endif
#include <format>
# endif
#endif
#include <iostream>

#if __cplusplus < 202002L
#error "only -std >= c++20 support std::format"
#endif

// error: invalid ‘#pragma GCC poison’ directive
//    12 | #pragma GCC poison std::format
//       |                       ^~
//#pragma GCC poison std::format

std::string tl_format(void)
{
#ifdef STD_FORMAT
#pragma message "Support std::format()"
	return std::format("$${}_{}", "Hello", "World");
#else
	return std::string("$$") + std::string("Hello") + std::string("_") + std::string("World");
#endif
}

int main(void)
{
	std::cout << tl_format() << std::endl;
	return 0;
}
