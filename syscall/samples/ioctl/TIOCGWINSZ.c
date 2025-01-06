#include <stdio.h>
#include <sys/ioctl.h>

int main(void)
{
	struct winsize sz;

	ioctl(fileno(stdin), TIOCGWINSZ, &sz);

#if defined(__sw_64__)
	printf("TIOCGWINSZ = %#08lx\n", TIOCGWINSZ);
#else
	printf("TIOCGWINSZ = %#08x\n", TIOCGWINSZ);
#endif
	printf("col: %i, row: %i, xpixel: %i, ypixel: %i\n",
	       sz.ws_col, sz.ws_row, sz.ws_xpixel, sz.ws_ypixel);

	return 0;
}
