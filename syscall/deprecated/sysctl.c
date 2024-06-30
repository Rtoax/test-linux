#include <sysctl.h>

int sysctl(int *names, int nlen, void *oldval, size_t *oldlenp, void *newval,
	   size_t newlen);

int main(void)
{
	return 0;
}

