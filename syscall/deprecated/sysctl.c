#include <unistd.h>
#include <sys/syscall.h>
#include <linux/sysctl.h>

int sysctl(int *names, int nlen, void *oldval, size_t *oldlenp, void *newval,
	   size_t newlen)
{
	return syscall(__NR__sysctl, names, nlen, oldval, oldlenp, newval, newlen);
}

int main(void)
{
	return 0;
}

