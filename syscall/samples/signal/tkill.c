#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <signal.h>

#ifndef SYS_tkill
#define SYS_tkill 238
#endif

static pid_t child_tid;

void* thread_func(void* arg)
{
	child_tid = syscall(SYS_gettid);
	printf("child thread tid %d\n", child_tid);
	while (1) {
		sleep(1);
		printf("child running...\n");
	}
	return NULL;
}

int main(void)
{
	pthread_t thread;
	int ret;

	ret = pthread_create(&thread, NULL, thread_func, NULL);
	if (ret != 0) {
		perror("pthread_create %m");
		exit(1);
	}
	sleep(1);

	printf("send signal SIGTERM to TID=%d\n", child_tid);

#ifdef TGKILL
	ret = tgkill(getpid(), child_tid, SIGTERM);
#else
	ret = syscall(SYS_tkill, child_tid, SIGTERM);
#endif
	if (ret == -1) {
		perror("tkill failed");
	}

	pthread_join(thread, NULL);
	return 0;
}
