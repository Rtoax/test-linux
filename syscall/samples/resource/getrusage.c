#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
	struct rusage rusage;

	getrusage(RUSAGE_SELF, &rusage);

	printf ("CPU time: %ld.%06ld sec user, %ld.%06ld sec system\n",
		rusage.ru_utime.tv_sec, rusage.ru_utime.tv_usec,
		rusage.ru_stime.tv_sec, rusage.ru_stime.tv_usec);
	printf("maxrss = %ld\n", rusage.ru_maxrss);
	printf("ixrss = %ld\n", rusage.ru_ixrss);
	printf("isrss = %ld\n", rusage.ru_isrss);
	printf("idrss = %ld\n", rusage.ru_idrss);

	return 0;
}

