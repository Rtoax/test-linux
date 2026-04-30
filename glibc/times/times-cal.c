#include <stdio.h>
#include <stdint.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

void start_clock(void)
{
	st_time = times(&st_cpu);
}

/* This example assumes that the result of each subtraction
 * is within the range of values that can be represented in
 * an integer type. */
void end_clock(void)
{
	en_time = times(&en_cpu);
	printf("Real Time: %jd, User Time %jd, System Time %jd\n",
		(intmax_t)(en_time - st_time),
		(intmax_t)(en_cpu.tms_utime - st_cpu.tms_utime),
		(intmax_t)(en_cpu.tms_stime - st_cpu.tms_stime));
}

int main(void)
{
	long int i;
	long int sum = 0;

	start_clock();
	sleep(1);

	for (i = 0; i < 100000000; i++) {
	    sum += i;
	}
	(void)sum;
	end_clock();
	return 0;
}
