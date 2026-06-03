#include <ncurses.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	keypad(stdscr, TRUE);
	/**
	 * nodelay configures the input character reading function to be
	 * non-blocking for window win.
	 */
	nodelay(stdscr, TRUE);

	while (1) {
		/* actually, getch() read from stdin */
		int c = getch();
		if (c != ERR) {
			switch (c) {
			case KEY_LEFT:
				printw("KEY_LEFT %d\n", c);
				break;
			default:
				printw("getch = '%c' %d\n", c, c);
				break;
			}
			refresh();
			switch (c) {
			case 'q':
				goto end;
				break;
			}
		}
	}

end:
	endwin();
	return 0;
}
