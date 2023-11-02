#include <sched.h>
#include <errno.h>
#include <stdio.h>


int main(void)
{
	sched_yield();
	perror("sched_yield");
	return 0;
}
