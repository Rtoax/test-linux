#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(void)
{
	printf("%d.%d.%d\n", NCURSES_VERSION_MAJOR, NCURSES_VERSION_MINOR,
	       NCURSES_VERSION_PATCH);

	return 0;
}
