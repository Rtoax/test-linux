#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t winch_flag = 0;

void window_change(int signo)
{
	if (signo == SIGWINCH) {
		winch_flag = 1;
	}
}

void print_winsz(void)
{
	int err, rows, cols;

	clear();

	err = getmaxyx(stdscr, rows, cols);
	printw("screen rows %d, cols %d, err %d\n", rows, cols, err);

	rows = getmaxy(stdscr);
	cols = getmaxx(stdscr);
	printw("screen rows %d, cols %d\n", rows, cols);

	refresh();
}

int main(void)
{
	signal(SIGWINCH, window_change);

	initscr();

	print_winsz();

	while (1) {
		if (winch_flag) {
			winch_flag = 0;
			endwin();
			refresh();
			print_winsz();
		}
		napms(100);
	}

	endwin();
	return 0;
}
