#include <ncurses.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	printw("Hello World.\n");
	refresh();
	sleep(1);

	WINDOW *warn_win = newwin(10, 10, 2, 2);
	box(warn_win, 0, 0);
	wprintw(warn_win, "New Window");
	wrefresh(warn_win);
	sleep(1);
	werase(warn_win);
	wrefresh(warn_win);
	delwin(warn_win);

	sleep(1);

	endwin();
	return 0;
}
