#include <sys/timex.h>
#include <time.h>
#include <stdio.h>

int print_ntptimeval(struct ntptimeval *ntv)
{
	printf("time.tv_sec = %ld\n", ntv->time.tv_sec);
	printf("time.tv_usec = %ld\n", ntv->time.tv_usec);
	printf("maxerror = %ld\n", ntv->maxerror);
	printf("esterror = %ld\n", ntv->esterror);
	printf("tai = %ld\n", ntv->tai);
	return 0;
}

int main(void)
{
	struct ntptimeval ntv;

	printf("ntp_gettime = %d\n", ntp_gettime(&ntv));
	print_ntptimeval(&ntv);

	printf("ntp_gettimex = %d\n", ntp_gettimex(&ntv));
	print_ntptimeval(&ntv);

	return 0;
}
