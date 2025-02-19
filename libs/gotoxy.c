#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "gotoxy.h"

#define P() do { \
		fprintf(stdout, "\033[1;%dm#\033[m", 7); \
		fflush(stdout); \
		usleep(300); \
	} while (0)
#define MIN(x, y) (x > y ? y : x)

int main(void)
{
	int x, y, bnd;
	unsigned short row, col;

	bnd = 5;

	getwinsz(&row, &col);

	for (bnd = 5; bnd < MIN(row, col) / 2 + 1; bnd += 3) {
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
	}

	printf("\n");
	return 0;
}
