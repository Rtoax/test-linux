#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>


struct thread_arg {
	char *name;
	unsigned long *pt;
};

