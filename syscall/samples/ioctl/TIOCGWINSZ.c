#include <stdio.h>
#include <sys/ioctl.h>

int main(void)
{
	struct winsize sz;

	ioctl(fileno(stdin), TIOCGWINSZ, &sz);

	printf("TIOCGWINSZ = %#08lx\n", TIOCGWINSZ);
	printf("%i, %i, %i, %i\n",
		sz.ws_col, sz.ws_row, sz.ws_xpixel, sz.ws_ypixel);

	return 0;
}
