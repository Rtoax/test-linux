#include <stdio.h>

#define __unused __attribute__((unused))


int main(void)
{
	const char __unused *s1 = "rongtao";
	const char __unused * const s2 = "rongtao";

	s1 = "hello";
	/* Forbidden */
	//s2 = "hello";

	return 0;
}
