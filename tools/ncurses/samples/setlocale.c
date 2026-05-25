#include <ncurses.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");
	initscr();
	curs_set(0);

	mvprintw(2, 2, "▄");

	refresh();
	getch();
	endwin();
	return 0;
}
