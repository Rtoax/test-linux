#define _SDT_HAS_SEMAPHORES 1

#include <sys/sdt.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#define __unused __attribute__ ((unused))
#define __sec_probes __attribute__ ((section (".probes")))
#define __hidden __attribute__ ((visibility ("hidden")))

__extension__
unsigned short tracetest_testprobe_semaphore __unused __sec_probes __hidden;

long myclock(void)
{
	char buffer[100];
	struct timeval tv;
	gettimeofday(&tv, NULL);
	sprintf(buffer, "tracetest_testprobe_semaphore: %d", tracetest_testprobe_semaphore);
	DTRACE_PROBE2(tracetest,  testprobe,  tv.tv_sec, buffer);
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
