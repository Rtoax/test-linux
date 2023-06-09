#include <stdio.h>
#include <sys/ioctl.h>

int main(void)
{
	struct winsize sz;

	ioctl(fileno(stdin), TIOCSWINSZ, &sz);

#if defined(__sw_64__)
	printf("TIOCSWINSZ = %#08lx\n", TIOCSWINSZ);
#else
	printf("TIOCSWINSZ = %#08x\n", TIOCSWINSZ);
#endif
	printf("%i, %i, %i, %i\n",
		sz.ws_col, sz.ws_row, sz.ws_xpixel, sz.ws_ypixel);

	return 0;
}
