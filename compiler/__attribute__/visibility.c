#include <stdio.h>

#define EXPORT __attribute__((visibility("default")))
#define INTERNAL __attribute__((visibility("hidden")))

EXPORT void foo(void)
{
}

INTERNAL void bar(void)
{
}

int main(void)
{
	foo();
	bar();
	return 0;
}
