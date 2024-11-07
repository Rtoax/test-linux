#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int nice_self(int increment)
{
	int result, old;

	old = getpriority(PRIO_PROCESS, 0);
	fprintf(stderr, "old priority %d\n", old);

	result = setpriority(PRIO_PROCESS, 0, old + increment);
	if (result != -1)
		return old + increment;
	else
		return -1;
}

int main(void)
{
	nice_self(1);
	nice(2);
	nice_self(3);
	return 0;
}
