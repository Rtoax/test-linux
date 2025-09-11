#include <common.h>

bool debug = false;

unsigned long power_of_2(unsigned long v)
{
	unsigned long ret = 2;

	while (ret < v)
		ret <<= 1;

	return ret;
}

void print_ansi(void)
{
	int i;
	for (i = 0; i < NR_ANSI; i++)
		printf("%4d %s   %s\n", i, ANSI_COLORS_GRAY[i], ANSI_COLORS_RESET);
}

#if TEST

void round(void)
{
	int i;
	for (i = 0; i < 1024; i+=10) {
		linfo("%d %d %d\n", i, ROUND_DOWN(i, 32), ROUND_UP(i, 32));
	}
}
#endif
