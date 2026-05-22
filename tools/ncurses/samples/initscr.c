#include <ncurses.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	endwin();
	return 0;
}
