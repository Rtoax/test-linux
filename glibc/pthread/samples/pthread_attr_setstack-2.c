#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/prctl.h>
#include <ctype.h>

#include <libs/memshow.h>
#include <macro/unused.h>

#define DBG_PRINT(fmt, args...) { \
	printf("%s %d ", __FUNCTION__, __LINE__); \
	printf(fmt,##args); \
	}

#define BUFFER_LEN 0x3000

void *testThead1(void *arg)
{
	prctl(PR_SET_NAME, "zoobiTask1");

	char __unused buffer[BUFFER_LEN];
	while (1) {
		DBG_PRINT("Start\n");
		sleep(1);
		DBG_PRINT("End\n");
	}
}

#define THREAD_STACK_LEN 0x4001
int main(int argc, const char *argv[])
{
	pthread_t thread1ID;
	pthread_attr_t attr;

	int ret = 0;
	void *stackAddr = NULL;
	int paseSize = getpagesize();

	DBG_PRINT("The linux page size:0x%x\n", paseSize);

	pthread_attr_init(&attr);
	ret = posix_memalign(&stackAddr, paseSize, THREAD_STACK_LEN);
	if (0 != ret) {
		DBG_PRINT("posix_memalign failed, errno:%s\n", strerror(ret));
		return -1;
	}
#if 1
	ret = pthread_attr_setstack(&attr, stackAddr, THREAD_STACK_LEN);
	if (0 != ret) {
		DBG_PRINT("pthread_attr_setstack failed, errno:%s\n",
			  strerror(ret));
		return -1;
	}
#endif
	void *getstackaddr = NULL;
	size_t getstackSize = 0;
	pthread_attr_getstack(&attr, &getstackaddr, &getstackSize);
	DBG_PRINT
	    ("pthread_attr_getstack>>getstackaddr:%p, getstackSize:0x%lx\n",
	     getstackaddr, getstackSize);

	ret = pthread_create(&thread1ID, &attr, testThead1, NULL);
	if (ret != 0) {
		DBG_PRINT("pthread_create failed! errno:%s\n", strerror(ret));
		return -1;
	}
	pthread_detach(thread1ID);

	while (1) {
		sleep(1);
	}

	return 0;
}
