#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
	struct rusage rusage;
	getrusage(RUSAGE_SELF, &rusage);
	printf("maxrss = %ld\n", rusage.ru_maxrss);
	printf("ixrss = %ld\n", rusage.ru_ixrss);
	printf("isrss = %ld\n", rusage.ru_isrss);
	printf("idrss = %ld\n", rusage.ru_idrss);
	return 0;
}

