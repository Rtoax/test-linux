#include <sys/sdt.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef __always_inline
#define __always_inline __attribute__((always_inline))
#endif

__always_inline inline static void myclock()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	DTRACE_PROBE2(tracetest, testprobe, tv.tv_sec, "Hello world");
}

static void mywrapper()
{
	myclock();
}

static void loop()
{
	while (1)
	{
		myclock();
		mywrapper();
		sleep(1);
	}
}

int main(int argc, char **argv __attribute__((unused)))
{
	if (argc > 1)
		return 0;

	loop();

	return 0;
}
