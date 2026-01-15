#include <iostream>

namespace threads
{
int _nthreads = 0;

int reset(void)
{
	_nthreads = 1024;
	return 0;
}

int print_info(void)
{
	std::cout << "_nthreads = " << threads::_nthreads << std::endl;
	return 0;
}
}

int main(void)
{
	threads::reset();
	threads::print_info();

	return 0;
}
