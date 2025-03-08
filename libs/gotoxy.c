#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "gotoxy.h"

#define WHITE	7
#define RED	31
#define GREEN	32
#define YELLOW	33
#define P(color, us) do { \
		fprintf(stdout, "\033[7;%dm \033[m", color); \
		fflush(stdout); \
		usleep(us); \
	} while (0)
#define MIN(x, y) (x > y ? y : x)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void fang(unsigned short row, unsigned short col, int bnd, int color, int us)
{
	int x, y;

	for (y = bnd; y < row - bnd; y++) {
		gotoxy(bnd, y);
		P(color, us);
	}

	for (x = bnd; x < col - bnd; x++) {
		gotoxy(x, y);
		P(color, us);
	}

	for (y = y; y >= bnd; y--) {
		gotoxy(x, y);
		P(color, us);
	}

	for (x = x; x >= bnd; x--) {
		gotoxy(x, y);
		P(color, us);
	}
}

int main(void)
{
	int bnd, i;
	unsigned short row, col;
	int colors[] = { WHITE, RED, GREEN, YELLOW };

	getwinsz(&row, &col);

	for (i = 0; i < ARRAY_SIZE(colors); i++) {
		for (bnd = 4; bnd < MIN(row, col) / 2; bnd += 2) {
			fang(row, col, bnd, colors[i], 10);
		}
		for (bnd = MIN(row, col) / 2; bnd > 2; bnd -= 2) {
			fang(row, col, bnd, colors[i], 10);
		}
	}

	printf("\n");
	return 0;
}
