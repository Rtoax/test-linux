/**
 * C++98: 199711L
 * C++03: 199711L (same as C++98)
 * C++11: 201103L
 * C++14: 201402L
 * C++17: 201703L
 * C++20: 202002L
 * C++23: 202302L
 * C++23: 202302L (not exist yet)
 *
 * Example: -std=c++98
 */
#include <iostream>
#include <cstdio>

int main(void)
{
	printf("__STDC__: %d\n", __STDC__);
	std::cout << "__cplusplus: " << __cplusplus << std::endl;
	printf("__cplusplus: %ld\n", __cplusplus);
	return 0;
}
