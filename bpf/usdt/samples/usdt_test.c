#include <sys/sdt.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long myclock(void)
{
	char hello1[] = "Hello world1";
	char hello2[] = "Hello world2";
	char hello3[] = "Hello world3";

	struct timeval tv;
	gettimeofday(&tv, NULL);
	// hello1 must be local
	DTRACE_PROBE2(tracetest,  testprobe,  tv.tv_sec, hello1);
	DTRACE_PROBE2(tracetest,  testprobe2, tv.tv_sec, hello2);
	DTRACE_PROBE2(tracetest2, testprobe2, tv.tv_sec, hello3);
	return tv.tv_sec;
}

int main(int argc, char **argv)
{
	if (argc > 1)
		return 0;

	while (1) {
		myclock();
		sleep(1);
	}
	return 0;
}
