#include <ncurses.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int err, rows, cols;

	initscr();

	err = getmaxyx(stdscr, rows, cols);
	printw("screen rows %d, cols %d, err %d\n", rows, cols, err);

	rows = getmaxy(stdscr);
	cols = getmaxx(stdscr);
	printw("screen rows %d, cols %d\n", rows, cols);

	refresh();
	sleep(1);

	endwin();
	return 0;
}
