#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "color.h"

chtype attrs[] = {
	A_NORMAL,     A_ATTRIBUTES, A_CHARTEXT, A_COLOR,      A_STANDOUT,
	A_UNDERLINE,  A_REVERSE,    A_BLINK,	A_DIM,	      A_BOLD,
	A_ALTCHARSET, A_INVIS,	    A_PROTECT,	A_HORIZONTAL, A_LEFT,
	A_LOW,	      A_RIGHT,	    A_TOP,	A_VERTICAL,   A_ITALIC,
};
struct attr_name_st {
	chtype v;
	const char *name;
} __attr_names[] = {
	{ .v = A_NORMAL, .name = "A_NORMAL", },
	{ .v = A_ATTRIBUTES, .name = "A_ATTRIBUTES", },
	{ .v = A_CHARTEXT, .name = "A_CHARTEXT", },
	{ .v = A_COLOR, .name = "A_COLOR", },
	{ .v = A_STANDOUT, .name = "A_STANDOUT", },
	{ .v = A_UNDERLINE, .name = "A_UNDERLINE", },
	{ .v = A_REVERSE, .name = "A_REVERSE", },
	{ .v = A_BLINK, .name = "A_BLINK", },
	{ .v = A_DIM, .name = "A_DIM", },
	{ .v = A_BOLD, .name = "A_BOLD", },
	{ .v = A_ALTCHARSET, .name = "A_ALTCHARSET", },
	{ .v = A_INVIS, .name = "A_INVIS", },
	{ .v = A_PROTECT, .name = "A_PROTECT", },
	{ .v = A_HORIZONTAL, .name = "A_HORIZONTAL", },
	{ .v = A_LEFT, .name = "A_LEFT", },
	{ .v = A_LOW, .name = "A_LOW", },
	{ .v = A_RIGHT, .name = "A_RIGHT", },
	{ .v = A_TOP, .name = "A_TOP", },
	{ .v = A_VERTICAL, .name = "A_VERTICAL", },
	{ .v = A_ITALIC, .name = "A_ITALIC", },
};

const char *attr_name(chtype a)
{
	for (int i = 0; i < sizeof(__attr_names) / sizeof(__attr_names[0]);
	     i++) {
		if (a == __attr_names[i].v)
			return __attr_names[i].name;
	}
	return "??";
}

void print_attr(void)
{
	clear();
	for (int i = 0; i < C_MAX; i++) {
		chtype c = colors[i];
		for (int j = 0; j < sizeof(attrs) / sizeof(attrs[0]); j++) {
			chtype a = attrs[j];
			attron(c | a);
			printw("[%s, %s]", color_names[i], attr_name(attrs[j]));
			attroff(c | a);
		}
	}
	printw("\nPress 'q' or ctrl-c to quit\n");
	refresh();
}

int main(void)
{
	initscr();

	init_colors();

	print_attr();

	while (getch() != 'q') {
		sleep(1);
	}

	endwin();
	return 0;
}
