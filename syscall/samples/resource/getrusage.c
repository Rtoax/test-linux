#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
	struct rusage rusage;
	getrusage(RUSAGE_SELF, &rusage);
	printf("maxrss = %ld\n", rusage.ru_maxrss);
	return 0;
}

