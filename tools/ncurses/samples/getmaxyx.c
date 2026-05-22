#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void print_winsz(void);

void window_change(int signo)
{
	if (signo == SIGWINCH) {
		print_winsz();
	}
}

/* TODO: why rows and cols not change? */
void print_winsz(void)
{
	int err, rows, cols;

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

	while (1)
		sleep(10);

	endwin();
	return 0;
}
