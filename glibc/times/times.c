#include <stdio.h>
#include <sys/times.h>

int main(void)
{
	struct tms buf;

	clock_t ct = times(&buf);

	printf("%ld:%ld:%ld:%ld, ct:%ld\n",
		buf.tms_utime,
		buf.tms_stime,
		buf.tms_cutime,
		buf.tms_cstime,
		ct);

	return 0;
}
