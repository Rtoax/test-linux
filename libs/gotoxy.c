#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "gotoxy.h"

#define P() do { \
		fprintf(stdout, "\033[1;7m#\033[m"); \
		fflush(stdout); \
		usleep(1000); \
	} while (0)

int main(void)
{
	int x, y, bnd;
	struct winsize sz;

	ioctl(fileno(stdin), TIOCGWINSZ, &sz);
	printf("col: %i, row: %i, xpixel: %i, ypixel: %i\n",
	       sz.ws_col, sz.ws_row, sz.ws_xpixel, sz.ws_ypixel);

	bnd = 5;

	for (y = bnd; y < sz.ws_row - bnd; y++) {
		gotoxy(bnd, y);
		P();
	}

	for (x = bnd; x < sz.ws_col - bnd; x++) {
		gotoxy(x, y);
		P();
	}

	for (y = y; y >= bnd; y--) {
		gotoxy(x, y);
		P();
	}

	for (x = x; x >= bnd; x--) {
		gotoxy(x, y);
		P();
	}

	printf("\n");
	return 0;
}
