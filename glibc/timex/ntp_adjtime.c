#include <sys/timex.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
	struct timex t;
	printf("%d\n", ntp_adjtime(&t));
	return 0;
}
