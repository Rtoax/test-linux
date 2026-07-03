#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "color.h"

int rgb_to_256(int r, int g, int b)
{
	return 16 + (r * 6 / 256) * 36 + (g * 6 / 256) * 6 + (b * 6 / 256);
}

void print_colors(void)
{
	clear();
	printw("COLORS = %d\n", COLORS);
	printw("COLOR_PAIRS = %d\n", COLOR_PAIRS);

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	(void)max_y;

	for (int i = 0; i < max_x; i++) {
		int red = (i * 255) / max_x;
		int color_idx = rgb_to_256(red, 0, 0);

		init_pair(i + 1, color_idx, COLOR_BLACK);

		chtype color = COLOR_PAIR(i + 1);

		attron(color | A_REVERSE);
		printw("X");
		attroff(color | A_REVERSE);
	}

	refresh();
}

int main(void)
{
	initscr();

	start_color();

	print_colors();

	printw("\nPress any key to quit\n");
	refresh();
	getch();

	endwin();
	return 0;
}
