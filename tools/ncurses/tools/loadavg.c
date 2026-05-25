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
#include <argp.h>
#include <errno.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "value.h"

static const char *verstring = "github.com/rtoax/test-linux v1.0.1";
const char argp_prog_doc[] = "USAGE: [-T|--title=<TITLE>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "title", 'T', "TITLE", 0, "Spedify title" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

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
static int height = 0, width = 0;
static int plotheight = 0, plotwidth = 0;

static struct timeval now;
static int sig_rd_fd, sig_wr_fd;
static int key = ' ';
static int done = false;
static int verbose = false;

static chtype flavor[8] = { 0 };

struct values load1 = {};
struct values load5 = {};
struct values load15 = {};

void sig_handler(int signo)
{
	int ret;
	do {
		ret = write(sig_wr_fd, &signo, 1);
	} while ((ret == -1) && (errno == EINTR));
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
		attron(flavor[color]);
		mvprintw(h, w, "━");
		attroff(flavor[color]);

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

void append_load(struct values *loads, double v)
{
	/* Only add new loadavg when the time interval is at least 1 second */
	if (loads->tail && loads->tail->tv.tv_sec == now.tv_sec)
		return;
	enqueue_val(loads, v);
	for (int i = plotwidth - 2; i < loads->count; i++)
		dequeue_val(loads);
}

void draw_axes(void)
{
	mvhline(plotheight + HEIGHT_BND, WIDTH_BND, T_HLINE, plotwidth);
	mvvline(HEIGHT_BND, WIDTH_BND, T_VLINE, plotheight);
	mvaddch(plotheight + HEIGHT_BND, WIDTH_BND, T_LLCR);
	mvaddch(HEIGHT_BND, WIDTH_BND, T_UARR);
	mvprintw(HEIGHT_BND, WIDTH_BND, "▲");
	mvprintw(plotheight + HEIGHT_BND, plotwidth + WIDTH_BND, "►");
}

void paint_plot(void)
{
	double loadavg[3];

	erase();

	mvaddstr(0, (width - strlen(title)) / 2, title);

	draw_axes();

	/* draw load */
	getloadavg(loadavg, 3);

	append_load(&load1, loadavg[0]);
	append_load(&load5, loadavg[1]);
	append_load(&load15, loadavg[2]);

#ifdef DEBUG
	mvprintw(0, 1, "- %d - %f - %lf~%lf", load1.count, loadavg[0],
		 load1.min->v, load1.max->v);
	mvprintw(1, 1, "- %d - %f - %lf~%lf", load5.count, loadavg[1],
		 load5.min->v, load5.max->v);
	mvprintw(2, 1, "- %d - %f - %lf~%lf", load15.count, loadavg[2],
		 load15.min->v, load15.max->v);
#endif

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

	time_t sec = time(NULL);
	struct tm *tm = localtime(&sec);
	char ts[64] = { 0 };
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\n';
	mvaddstr(height - 2, width - strlen(ts) - 1, ts);

	mvaddstr(height - 1, width - strlen(verstring) - 1, verstring);

#ifdef DEBUG
	mvprintw(height - 2, 1,
		 "%.2f %.2f %.2f, row %d (%d), col %d (%d), key '%d'\n",
		 loadavg[0], loadavg[1], loadavg[2], LINES, plotheight, COLS,
		 plotwidth, key);
#endif
	move(0, 0);
}

void redraw_screen(void)
{
	paint_plot();
	refresh();
}

static error_t parse_arg(int opt, char *arg, struct argp_state *state)
{
	switch (opt) {
	case 'T':
		title = arg;
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

int main(int argc, char *argv[])
{
	int maxfd = STDIN_FILENO;
	int timerfd;
	int sigpipe[2];
	fd_set readfds;

	int err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	setlocale(LC_ALL, "");

	if (pipe(sigpipe) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	sig_rd_fd = sigpipe[0];
	sig_wr_fd = sigpipe[1];

	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);

	gettimeofday(&now, NULL);

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

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
	struct itimerspec tmout = { { 1, 0 }, { 1, 0 } };
	timerfd_settime(timerfd, 0, &tmout, NULL);
	FD_SET(timerfd, &readfds);
	if (maxfd < timerfd)
		maxfd = timerfd;

	FD_SET(sig_rd_fd, &readfds);
	if (maxfd < sig_rd_fd)
		maxfd = sig_rd_fd;

	update_size();
	redraw_screen();

	/* main loop */
	while (!done) {
		fd_set fds = readfds;
		bool redraw = false;

		int ret = select(maxfd + 1, &fds, NULL, NULL, NULL);
		gettimeofday(&now, NULL);
		if (ret > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
			key = getch();
			switch (key) {
			case 'q':
				goto end;
				break;
			case 13: /* enter */
				redraw = true;
				break;
			}
		} else if (ret > 0 && FD_ISSET(timerfd, &fds)) {
			uint64_t exp;
			read(timerfd, &exp, sizeof(exp));
			redraw = true;
		} else if (ret > 0 && FD_ISSET(sig_rd_fd, &fds)) {
			int signo;
			read(sig_rd_fd, &signo, 1);
			if (signo == SIGINT) {
				break;
			} else if (signo == SIGWINCH) {
				endwin();
				initscr();
				erase();
				refresh();
				update_size();
				redraw = true;
			}
		} else
			continue;

		if (redraw)
			redraw_screen();
	}

end:
	endwin();
	return 0;
}
