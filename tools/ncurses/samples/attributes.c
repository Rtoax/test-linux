#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

enum color_enum {
	C_GREEN,
	C_RED,
	C_CYAN,
	C_WHITE,
	C_MAGENTA,
	C_BLUE,
	C_YELLOW,
	C_MAX,
	C_UNKNOWN = C_MAX,
};
char *color_names[] = {
	[C_GREEN] = "GREEN",   [C_RED] = "RED",		[C_CYAN] = "CYAN",
	[C_WHITE] = "WHITE",   [C_MAGENTA] = "MAGENTA", [C_BLUE] = "BLUE",
	[C_YELLOW] = "YELLOW",
};

chtype colors[C_MAX] = { 0 };
chtype attrs[] = {
	A_NORMAL,     A_ATTRIBUTES, A_CHARTEXT, A_COLOR,      A_STANDOUT,
	A_UNDERLINE,  A_REVERSE,    A_BLINK,	A_DIM,	      A_BOLD,
	A_ALTCHARSET, A_INVIS,	    A_PROTECT,	A_HORIZONTAL, A_LEFT,
	A_LOW,	      A_RIGHT,	    A_TOP,	A_VERTICAL,   A_ITALIC,
};

void init_colors(void)
{
	if (has_colors()) {
		int bg = COLOR_BLACK;
		start_color();
#define SET_COLOR(num, fg)                        \
	init_pair(num + 1, (short)fg, (short)bg); \
	colors[num] |= (chtype)COLOR_PAIR(num + 1)

		SET_COLOR(C_GREEN, COLOR_GREEN);
		SET_COLOR(C_RED, COLOR_RED);
		SET_COLOR(C_CYAN, COLOR_CYAN);
		SET_COLOR(C_WHITE, COLOR_WHITE);
		SET_COLOR(C_MAGENTA, COLOR_MAGENTA);
		SET_COLOR(C_BLUE, COLOR_BLUE);
		SET_COLOR(C_YELLOW, COLOR_YELLOW);
#undef SET_COLOR
	}
}

void print_attr(void)
{
	clear();
	for (int i = 0; i < C_MAX; i++) {
		chtype c = colors[i];
		for (int j = 0; j < sizeof(attrs) / sizeof(attrs[0]); j++) {
			chtype a = attrs[j];
			attron(c | a);
			printw("%s", color_names[i]);
			attroff(c | a);
		}
	}
	refresh();
}

int main(void)
{
	initscr();

	init_colors();

	print_attr();

	while (getch() != 'q') {
		sleep(1);
	}

	endwin();
	return 0;
}
