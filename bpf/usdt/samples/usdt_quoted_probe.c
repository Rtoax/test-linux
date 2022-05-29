#include <stdio.h>
#include <unistd.h>
#include <sys/sdt.h>

int main(int argc, char **argv)
{
	if (argc > 1)
		return 0;

	int a = 1;
	// For some reason some compilers think `a` is unused
	(void)a;

	while (1) {
		DTRACE_PROBE1(test, "probe1", a);
		sleep(1);
	}

	return 0;
}
