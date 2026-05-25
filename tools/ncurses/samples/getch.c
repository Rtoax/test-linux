#include <ncurses.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	while (1) {
		char c = getch();
		printw("getch = '%c' %d\n", c, c);
		refresh();
		switch (c) {
		case 'q':
			goto end;
			break;
		}
	}

end:
	endwin();
	return 0;
}
