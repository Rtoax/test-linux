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
static const int height_bnd = 3, width_bnd = 6;

static int done = false;

static chtype flavor[8] = { 0 };

struct value {
	double v;
	struct value *next;
};

struct values {
	struct value *head, *tail, *max;
	int count; /* number of value */
};

struct values load1 = {};
struct values load5 = {};
struct values load15 = {};

#define for_each_value(vals, iter)                                       \
	for (struct value *iter = ((struct values *)(vals))->head; iter; \
	     iter = iter->next)

int dequeue_val(struct values *vals)
{
	if (!vals || !vals->head)
		return 0;
	int v = vals->head->v;
	/* update max */
	if (vals->max && vals->max == vals->head) {
		struct value *tmp = vals->max = vals->head->next;
		while (tmp) {
			if (tmp->v > vals->max->v)
				vals->max = tmp;
			tmp = tmp->next;
		}
	}
	vals->count--;
	vals->head = vals->head->next;
	return v;
}

int enqueue_val(struct values *vals, double v)
{
	struct value *new = malloc(sizeof(struct value));
	new->v = v;
	new->next = NULL;

	if (!vals->head) {
		vals->head = new;
		vals->count = 1;
	} else {
		vals->tail->next = new;
		vals->count++;
	}

	if (!vals->max) {
		vals->max = new;
	} else {
		if (vals->max->v < v)
			vals->max = new;
	}

	vals->tail = new;
	return 0;
}

void sig_handler(int signo)
{
	switch (signo) {
	case SIGINT:
		done = true;
		break;
	}
}

void paint_plot(void)
{
	int i;
	double loadavg[3];
	int plotheight = height - height_bnd * 2;
	int plotwidth = width - width_bnd * 2;

	erase();

	mvaddstr(0, (width - strlen(title)) / 2, title);

	/* draw axes */
	mvhline(plotheight + height_bnd, width_bnd, T_HLINE, plotwidth);
	mvvline(height_bnd, width_bnd, T_VLINE, plotheight);
	mvaddch(plotheight + height_bnd, width_bnd, T_LLCR);
	mvaddch(height_bnd, width_bnd, T_UARR);
	mvaddch(plotheight + height_bnd, plotwidth + width_bnd, T_RARR);

	/* draw load */
	getloadavg(loadavg, 3);

	enqueue_val(&load1, loadavg[0]);
	enqueue_val(&load5, loadavg[1]);
	enqueue_val(&load15, loadavg[2]);

#ifdef DEBUG
	mvprintw(0, 1, "- %d - %f", load1.count, loadavg[0]);
	mvprintw(1, 1, "- %d - %f", load5.count, loadavg[1]);
	mvprintw(2, 1, "- %d - %f", load15.count, loadavg[2]);
#endif

	for (i = plotwidth - 2; i < load1.count; i++)
		dequeue_val(&load1);
	for (i = plotwidth - 2; i < load5.count; i++)
		dequeue_val(&load5);
	for (i = plotwidth - 2; i < load15.count; i++)
		dequeue_val(&load15);

	i = 0;
	for_each_value(&load1, v)
	{
		int h = plotheight + height_bnd -
			v->v * plotheight / load1.max->v;
		mvaddch(h, plotwidth + width_bnd - load1.count + i,
			T_HLINE | flavor[2]);
		i++;
		if (i == load1.count) {
			mvprintw(h, 0, "%.2f", v->v);
		}
	}

	// TODO: draw more

	mvaddstr(height - 1, width - strlen(verstring) - 1, verstring);
#ifdef DEBUG
	mvprintw(height - 2, 1, "%.2f %.2f %.2f, row %d (%d), col %d (%d)\n",
		 loadavg[0], loadavg[1], loadavg[2], LINES, plotheight, COLS,
		 plotwidth);
#endif
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
		napms(1000);
	}

	endwin();
	return 0;
}
