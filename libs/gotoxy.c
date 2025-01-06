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
	unsigned short row, col;

	bnd = 5;

	getwinsz(&row, &col);

	for (y = bnd; y < row - bnd; y++) {
		gotoxy(bnd, y);
		P();
	}

	for (x = bnd; x < col - bnd; x++) {
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
