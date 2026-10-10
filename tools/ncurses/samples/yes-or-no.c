#include <ncurses.h>
#include <string.h>
#include <locale.h>

// 1 = Yes，0 = No
int confirm(const char *title, const char *msg)
{
	int h = 7, w = 50;
	int y = (LINES - h) / 2;
	int x = (COLS - w) / 2;

	WINDOW *win = newwin(h, w, y, x);
	keypad(win, TRUE);

	int sel = 0; // 0 = Yes, 1 = No
	int ret = 0;

	while (1) {
		werase(win);
		box(win, 0, 0);

		// Title
		mvwprintw(win, 1, (w - (int)strlen(title)) / 2, "%s", title);

		mvwprintw(win, 3, 2, "%.*s", w - 4, msg);

		if (sel == 0)
			wattron(win, A_REVERSE);
		mvwprintw(win, 5, w / 2 - 8, "[ Yes ]");
		if (sel == 0)
			wattroff(win, A_REVERSE);

		if (sel == 1)
			wattron(win, A_REVERSE);
		mvwprintw(win, 5, w / 2 + 2, "[ No ]");
		if (sel == 1)
			wattroff(win, A_REVERSE);

		wrefresh(win);

		int ch = wgetch(win);
		switch (ch) {
		case 'y':
		case 'Y':
			ret = 1;
			goto done;

		case 'n':
		case 'N':
			ret = 0;
			goto done;

		case KEY_LEFT:
		case KEY_RIGHT:
		case '\t':
			sel = !sel;
			break;

		case '\n':
		case KEY_ENTER:
			ret = (sel == 0);
			goto done;

		case 27: // ESC is No
			ret = 0;
			goto done;
		}
	}

done:
	delwin(win);
	touchwin(stdscr);
	refresh();
	return ret;
}

int main(void)
{
	int opt;

	setlocale(LC_ALL, "");

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	opt = confirm("Confirm", "Are you sure?");

	endwin();

	printf("%s\n", opt ? "Yes" : "No");
	return 0;
}
