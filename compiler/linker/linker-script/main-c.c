#include "bar.h"
#include "foo.h"

int main_global_data1 = 0xa1;

int main(void)
{
	main_global_data1 = 2;
	foo();
	foo1();
	foo2();
	bar();
	return 0;
}
