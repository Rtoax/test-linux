#include "bar.h"
#include "foo.h"

int main1 = 1;

int main(void)
{
	main1 = 2;
	foo();
	foo1();
	foo2();
	bar();
	return 0;
}
