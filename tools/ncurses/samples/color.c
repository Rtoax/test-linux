#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
	initscr();

	start_color();

	printw("COLORS = %d\n", COLORS);
	printw("COLOR_PAIRS = %d\n", COLOR_PAIRS);

	while (getch() != 'q') {
		sleep(1);
	}

	endwin();
	return 0;
}
