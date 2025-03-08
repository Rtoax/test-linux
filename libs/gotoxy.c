#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "gotoxy.h"

#define WHITE	7
#define RED	31
#define P(color) do { \
		fprintf(stdout, "\033[1;%dm#\033[m", color); \
		fflush(stdout); \
		usleep(300); \
	} while (0)
#define MIN(x, y) (x > y ? y : x)

void fang(unsigned short row, unsigned short col, int bnd, int color)
{
	int x, y;

	for (y = bnd; y < row - bnd; y++) {
		gotoxy(bnd, y);
		P(color);
	}

	for (x = bnd; x < col - bnd; x++) {
		gotoxy(x, y);
		P(color);
	}

	for (y = y; y >= bnd; y--) {
		gotoxy(x, y);
		P(color);
	}

	for (x = x; x >= bnd; x--) {
		gotoxy(x, y);
		P(color);
	}
}

int main(void)
{
	int bnd;
	unsigned short row, col;

	bnd = 5;

	getwinsz(&row, &col);

	for (bnd = 4; bnd < MIN(row, col) / 2; bnd += 2) {
		fang(row, col, bnd, WHITE);
	}
	for (bnd = MIN(row, col) / 2; bnd > 2; bnd -= 2) {
		fang(row, col, bnd, RED);
	}

	printf("\n");
	return 0;
}
