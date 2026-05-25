// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
/**
 * Plot and display a loadavg graph of 1, 5, 15 minutes in the Linux terminal
 * with minimal dependencies.
 *
 * ttyplot is not good enough.
 *
 * see also test-linux/scripts/loadavg.sh
 *
 * ttyplot: https://github.com/tenox7/ttyplot.git
 */
#include <errno.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <ncurses.h>
#include <unistd.h>

#ifdef NOACS
#define T_HLINE '-'
#define T_VLINE '|'
#define T_LLCR 'L'
#define T_RARR '>'
#define T_UARR '^'
#else
#define T_HLINE ACS_HLINE
#define T_VLINE ACS_VLINE
#define T_LLCR ACS_LLCORNER
#define T_RARR ACS_RARROW
#define T_UARR ACS_UARROW
#endif

static char *title = "Load average";
static const char *verstring = "v0.0.1";
static int height = 0, width = 0;
static const int height_bnd = 3, width_bnd = 5;

static int done = false;

static chtype flavor[] = {
	'O', '*', '#', '$', '%', '0', '@',
};

void sig_handler(int signo)
{
	switch (signo) {
	case SIGINT:
		done = true;
		break;
	}
}

int getload(int *l1, int *l5, int *l15, int scale)
{
	FILE *fp = fopen("/proc/loadavg", "r");
	if (!fp) {
		fprintf(stderr, "open /proc/loadavg failed, %m\n");
		return -errno;
	}

	float load1, load5, load15;
	fscanf(fp, "%f %f %f", &load1, &load5, &load15);

	*l1 = load1 * scale;
	*l5 = load5 * scale;
	*l15 = load15 * scale;

	fclose(fp);
	return 0;
}

void paint_plot(void)
{
	int l1, l5, l15;
	int plotheight = height - height_bnd * 2;
	int plotwidth = width - width_bnd * 2;

	mvaddstr(0, (width - strlen(title)) / 2, title);

	/* draw axes */
	mvhline(plotheight + height_bnd, width_bnd, T_HLINE, plotwidth);
	mvvline(height_bnd, width_bnd, T_VLINE, plotheight);
	mvaddch(plotheight + height_bnd, width_bnd, T_LLCR);
	mvaddch(height_bnd, width_bnd, T_UARR);
	mvaddch(plotheight + height_bnd, plotwidth + width_bnd, T_RARR);

	/* draw load */
	getload(&l1, &l5, &l15, 1000);

	mvaddstr(height - 1, width - strlen(verstring) - 1, verstring);
	mvprintw(height - 2, 1, "%d %d %d, row %d, col %d\n", l1, l5, l15,
		 LINES, COLS);

	mvaddch(plotheight, plotwidth, 'X' | A_REVERSE);

	// TODO: draw more

	move(0, 0);
}

void redraw_screen(void)
{
	paint_plot();
	refresh();
}

int main(void)
{
	setlocale(LC_ALL, "");

	signal(SIGINT, sig_handler);
	initscr();
	cbreak();
	noecho();
	nonl();

	curs_set(0);

	if (has_colors()) {
		int bg = COLOR_BLACK;
		start_color();
#define SET_COLOR(num, fg)                        \
	init_pair(num + 1, (short)fg, (short)bg); \
	flavor[num] |= (chtype)COLOR_PAIR(num + 1) | A_BOLD

		SET_COLOR(0, COLOR_GREEN);
		SET_COLOR(1, COLOR_RED);
		SET_COLOR(2, COLOR_CYAN);
		SET_COLOR(3, COLOR_WHITE);
		SET_COLOR(4, COLOR_MAGENTA);
		SET_COLOR(5, COLOR_BLUE);
		SET_COLOR(6, COLOR_YELLOW);
#undef SET_COLOR
	}

	while (!done) {
		getmaxyx(stdscr, height, width);
		redraw_screen();
		napms(10);
	}

	endwin();
	return 0;
}
