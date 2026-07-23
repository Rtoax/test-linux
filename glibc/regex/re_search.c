#ifndef __USE_GNU
#define __USE_GNU 1
#endif
#include <regex.h>
#include <stdio.h>

int main(void)
{
	re_search(NULL, NULL, 0, 0, 0, NULL);
	return 0;
}
