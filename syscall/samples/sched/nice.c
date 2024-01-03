#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int nice_self(int increment)
{
	int result, old = getpriority(PRIO_PROCESS, 0);
	result = setpriority(PRIO_PROCESS, 0, old + increment);
	if (result != -1)
		return old + increment;
	else
		return -1;
}

int main(void)
{
	nice(1);
	nice_self(1);
	return 0;
}
