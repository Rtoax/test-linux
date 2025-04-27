#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "fork_helpers.h"

#if defined(TRY_FORK) || defined(TRY_VFORK)
void test_try_fork(void)
{
#ifdef TRY_VFORK
	try_fork(1, NULL);
#else
	try_fork(0, NULL);
#endif
}
#else
#define test_try_fork()
#endif

#if defined(TRY_POPEN)
void test_try_popen(void)
{
	try_popen(NULL);
}
#else
#define test_try_popen()
#endif

int main(int argc, char *argv[])
{
	unsigned long count = 0;
	while (1) {
		printf("Sleeping %ld s\n", count++);
		sleep(1);
		test_try_fork();
		test_try_popen();
	}
	return 0;
}
