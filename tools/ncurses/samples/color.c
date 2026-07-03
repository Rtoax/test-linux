#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "color.h"

void print_colors(void)
{
	clear();
	printw("COLORS = %d\n", COLORS);
	printw("COLOR_PAIRS = %d\n", COLOR_PAIRS);

	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	(void)max_y;
	for (int i = 0; i < max_x; i++) {
		int red = (i * 1000) / max_x;
		init_color(COLOR_RED, red, 0, 0);
		init_pair(i, COLOR_RED, COLOR_BLACK);
		chtype color = COLOR_PAIR(i + 1);

		attron(color);
		printw("X");
		attroff(color);
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
