#include <iostream>
#include <ostream>
#include <algorithm>
#include <csignal>
#include <list>

int main(void)
{
	std::cout << "static_cast<size_t>(MINSIGSTKSZ) = " << static_cast<size_t>(MINSIGSTKSZ) << std::endl;
	return 0;
}
