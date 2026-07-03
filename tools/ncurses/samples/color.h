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
const char *color_names[] = {
	[C_GREEN] = "GREEN",   [C_RED] = "RED",		[C_CYAN] = "CYAN",
	[C_WHITE] = "WHITE",   [C_MAGENTA] = "MAGENTA", [C_BLUE] = "BLUE",
	[C_YELLOW] = "YELLOW",
};

chtype colors[C_MAX] = { 0 };

void init_colors(void)
{
	if (has_colors()) {
		start_color();
#define SET_COLOR(num, fg)                                 \
	init_pair(num + 1, (short)fg, (short)COLOR_BLACK); \
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
