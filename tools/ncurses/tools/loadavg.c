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
#include <sys/time.h>
#include <time.h>
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

#define C_GREEN 0
#define C_RED 1
#define C_CYAN 2
#define C_WHITE 3
#define C_MAGENTA 4
#define C_BLUE 5
#define C_YELLOW 6

#define HEIGHT_BND 4
#define WIDTH_BND 6

static char *title = "Load average";
static const char *verstring = "github.com/rtoax/test-linux v0.0.1";
static int height = 0, width = 0;
static int plotheight = 0, plotwidth = 0;

static int done = false;

static chtype flavor[8] = { 0 };

struct value {
	double v;
	struct timeval tv;
	struct value *next;
};

struct values {
	struct value *head, *tail, *max, *min;
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
	/* update min */
	if (vals->min && vals->min == vals->head) {
		struct value *tmp = vals->min = vals->head->next;
		while (tmp) {
			if (tmp->v < vals->min->v)
				vals->min = tmp;
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
	gettimeofday(&new->tv, NULL);
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
	if (!vals->min) {
		vals->min = new;
	} else {
		if (vals->min->v > v)
			vals->min = new;
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

void update_size(void)
{
	getmaxyx(stdscr, height, width);
	plotheight = height - HEIGHT_BND * 2;
	plotwidth = width - WIDTH_BND * 2;
}

void paint_values(struct values *load, char *label, double max, double min,
		  int color)
{
	int i = 0;
	for_each_value(load, v)
	{
		int h = plotheight + HEIGHT_BND - 1 -
			(v->v - min) * (plotheight - 2) / (max - min);
		int w = plotwidth + WIDTH_BND - load->count + i;
		mvaddch(h, w, T_HLINE | flavor[color]);

		i++;

		/* set x axis */
		if ((i - 1) % 10 == 0) {
			char buf[10];
			strftime(buf, 10, "%T", localtime(&v->tv.tv_sec));
			mvprintw(height - HEIGHT_BND + 1, w, "%s", buf);
		}

		/* set y axis */
		attron(flavor[color]);
		mvprintw(h, 0, "%.3f", v->v);
		if (i == load->count)
			mvprintw(h, w + 1, "%s", label);
		attroff(flavor[color]);
	}
}

void paint_plot(void)
{
	int i;
	double loadavg[3];

	erase();

	mvaddstr(0, (width - strlen(title)) / 2, title);

	/* draw axes */
	mvhline(plotheight + HEIGHT_BND, WIDTH_BND, T_HLINE, plotwidth);
	mvvline(HEIGHT_BND, WIDTH_BND, T_VLINE, plotheight);
	mvaddch(plotheight + HEIGHT_BND, WIDTH_BND, T_LLCR);
	mvaddch(HEIGHT_BND, WIDTH_BND, T_UARR);
	mvaddch(plotheight + HEIGHT_BND, plotwidth + WIDTH_BND, T_RARR);

	/* draw load */
	getloadavg(loadavg, 3);

	enqueue_val(&load1, loadavg[0]);
	enqueue_val(&load5, loadavg[1]);
	enqueue_val(&load15, loadavg[2]);

#ifdef DEBUG
	mvprintw(0, 1, "- %d - %f - %lf~%lf", load1.count, loadavg[0],
		 load1.min->v, load1.max->v);
	mvprintw(1, 1, "- %d - %f - %lf~%lf", load5.count, loadavg[1],
		 load5.min->v, load5.max->v);
	mvprintw(2, 1, "- %d - %f - %lf~%lf", load15.count, loadavg[2],
		 load15.min->v, load15.max->v);
#endif

	for (i = plotwidth - 2; i < load1.count; i++)
		dequeue_val(&load1);
	for (i = plotwidth - 2; i < load5.count; i++)
		dequeue_val(&load5);
	for (i = plotwidth - 2; i < load15.count; i++)
		dequeue_val(&load15);

	double load_max = 0, load_min = 9999;
	load_max = load_max < load1.max->v ? load1.max->v : load_max;
	load_max = load_max < load5.max->v ? load5.max->v : load_max;
	load_max = load_max < load15.max->v ? load15.max->v : load_max;
	load_min = load_min > load1.min->v ? load1.min->v : load_min;
	load_min = load_min > load5.min->v ? load5.min->v : load_min;
	load_min = load_min > load15.min->v ? load15.min->v : load_min;

	paint_values(&load1, "load1", load_max, load_min, C_RED);
	paint_values(&load5, "load5", load_max, load_min, C_GREEN);
	paint_values(&load15, "load15", load_max, load_min, C_BLUE);

	struct timeval now;
	gettimeofday(&now, NULL);
	struct tm *tm = localtime(&now.tv_sec);
	char ts[64] = { 0 };
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\n';
	mvaddstr(height - 2, width - strlen(ts) - 1, ts);

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
	flavor[num] |= (chtype)COLOR_PAIR(num + 1)

		SET_COLOR(C_GREEN, COLOR_GREEN);
		SET_COLOR(C_RED, COLOR_RED);
		SET_COLOR(C_CYAN, COLOR_CYAN);
		SET_COLOR(C_WHITE, COLOR_WHITE);
		SET_COLOR(C_MAGENTA, COLOR_MAGENTA);
		SET_COLOR(C_BLUE, COLOR_BLUE);
		SET_COLOR(C_YELLOW, COLOR_YELLOW);
#undef SET_COLOR
	}

	while (!done) {
		update_size();

		redraw_screen();
		napms(1000);
	}

	endwin();
	return 0;
}
