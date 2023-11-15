#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


#define test(clk_id) { \
	printf("%s: %d\n", #clk_id, clk_id);\
}

int main(void)
{
	clockid_t clock_id=CLOCK_PROCESS_CPUTIME_ID;
	pid_t pid = getpid();
	int ret;

	ret = clock_getcpuclockid(pid, &clock_id);
	switch (ret) {
	case -ENOSYS:
		printf("The kernel does not support obtaining the per-process CPU-time clock of another process,\n");
		break;
	case -EPERM:
		printf("The  caller does not have permission to access the CPU-time clock of the process specified by pid\n");
		break;
	case -ESRCH:
		printf("There is no process with the ID pid.\n");
		break;
	default:
		printf("  success.\n");
		break;
	}
	printf("pid %d, %d\n", pid, clock_id);

	test(CLOCK_REALTIME);
	test(CLOCK_REALTIME_COARSE);
	test(CLOCK_MONOTONIC);
	test(CLOCK_MONOTONIC_COARSE);
	test(CLOCK_MONOTONIC_RAW);
	test(CLOCK_BOOTTIME);
	test(CLOCK_PROCESS_CPUTIME_ID);
	test(CLOCK_THREAD_CPUTIME_ID);
	return 0;
}


