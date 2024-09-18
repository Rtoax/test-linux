#include <string.h>

int main(int argc, char *argv[])
{
	char buf[1024] = {'x'};
	char buf2[1024];

#if defined(STRESS)
	/**
	 * Check with:
	 * $ sudo perf top -p $(pidof memcpy-stress)
	 */
	while (1)
#endif
		memcpy(buf2, buf, sizeof(buf));

	return 0;
}
