#include <stdio.h>
#include <sys/ioctl.h>

/**
 * row: 行; col: 列;
 *
 * $ tput sc                # save curse
 * $ tput cup [row] [col]   # jump to curse
 * $ tput rc                # resume curse
 */
static void __attribute__((unused))
gotoxy(int col, int row)
{
	printf("%c[%d;%df", 0x1B, row, col);
}

static int __attribute__((unused))
getwinsz(unsigned short *row, unsigned short *col)
{
	int ret;
	struct winsize sz;

	ret = ioctl(fileno(stdin), TIOCGWINSZ, &sz);

#ifdef DEBUG
	fprintf(stderr, "col: %i, row: %i, xpixel: %i, ypixel: %i\n",
		sz.ws_col, sz.ws_row, sz.ws_xpixel, sz.ws_ypixel);
#endif

	*row = sz.ws_row;
	*col = sz.ws_col;
	return ret;
}

