#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(void)
{
	WINDOW *std = initscr();
	if (!std) {
		fprintf(stderr, "initscr failed\n");
		exit(EXIT_FAILURE);
	}

	mvprintw(0, 0, "LINES=%d COLS=%d", LINES, COLS);

	WINDOW *a = newwin(5, 20, 1, 1);
	WINDOW *b = newwin(5, 20, 7, 1);

	box(a, 0, 0);
	mvwprintw(a, 1, 1, "Window A");

	box(b, 0, 0);
	mvwprintw(b, 1, 1, "Window B");

	wnoutrefresh(a);
	wnoutrefresh(b);
	doupdate();
	napms(1000);

	delwin(a);
	delwin(b);
	endwin();

	return 0;
}
