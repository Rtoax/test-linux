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
#include "plot.h"

static const char *verstring = "github.com/rtoax/test-linux v1.0.2";
const char argp_prog_doc[] = "USAGE: [-T|--title=<TITLE>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "title", 'T', "TITLE", 0, "Spedify title" },
	{ "interval", 'I', "INTERVAL SEC", 0, "Spedify interval seconds" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

static struct timeval now;
static int sig_rd_fd, sig_wr_fd;
static int key = ' ';
static int done = false;
static int verbose = false;

struct line load1 = {};
struct line load5 = {};
struct line load15 = {};

struct line_group line_group_loadavg = {};

struct plot pla = {
	.title = "Load average",
	.interval_sec = 1,
	.lg = &line_group_loadavg,
};

void sig_handler(int signo)
{
	int ret, saved_errno = errno;
	do {
		ret = write(sig_wr_fd, &signo, 1);
	} while ((ret == -1) && (errno == EINTR));
	errno = saved_errno;
}

void append_load(struct line *loads, double v)
{
	/* Only add new loadavg when the time interval is at least 1 second */
	if (loads->tail && loads->tail->tv.tv_sec == now.tv_sec)
		return;
	enqueue_val(loads, v);
	for (int i = pla.plotwidth - 2; i < loads->count; i++)
		dequeue_val(loads);
}

void paint_plot(const struct plot *p)
{
	erase();

	plot_draw_title(p);
	plot_draw_axes(p);

	double max = 0, min = 9999;
	for_each_line(p->lg, l)
	{
		max = max < l->max->v ? l->max->v : max;
		min = min > l->min->v ? l->min->v : min;
	}
	for_each_line(p->lg, l)
	{
		plot_paint_line(p, l, l->name, max, min, l->color);
	}

	time_t sec = time(NULL);
	struct tm *tm = localtime(&sec);
	char ts[64] = { 0 };
	asctime_r(tm, ts);
	ts[strlen(ts) - 1] = '\n';
	mvaddstr(p->height - 2, p->width - strlen(ts) - 1, ts);

	mvaddstr(p->height - 1, p->width - strlen(verstring) - 1, verstring);

	move(0, 0);
}

void redraw_screen(void)
{
	double avg[3];

	getloadavg(avg, 3);

	append_load(&load1, avg[0]);
	append_load(&load5, avg[1]);
	append_load(&load15, avg[2]);

#ifdef DEBUG
	mvprintw(0, 1, "- %d - %f - %lf~%lf", load1.count, avg[0], load1.min->v,
		 load1.max->v);
	mvprintw(1, 1, "- %d - %f - %lf~%lf", load5.count, avg[1], load5.min->v,
		 load5.max->v);
	mvprintw(2, 1, "- %d - %f - %lf~%lf", load15.count, avg[2],
		 load15.min->v, load15.max->v);

	mvprintw(pla.height - 2, 1,
		 "%.2f %.2f %.2f, row %d (%d), col %d (%d), key '%d'\n", avg[0],
		 avg[1], avg[2], LINES, pla.plotheight, COLS, pla.plotwidth,
		 key);
#endif

	paint_plot(&pla);
	refresh();
}

static error_t parse_arg(int opt, char *arg, struct argp_state *state)
{
	switch (opt) {
	case 'T':
		pla.title = arg;
		break;
	case 'I':
		pla.interval_sec = atoi(arg);
		if (pla.interval_sec <= 0) {
			fprintf(stderr, "ERROR: bad -I value\n");
			exit(EXIT_FAILURE);
		}
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

	init_flavor();

	init_line(&load1, "load1", flavor[C_RED]);
	init_line(&load5, "load5", flavor[C_GREEN]);
	init_line(&load15, "load15", flavor[C_BLUE]);

	line_group_add(&line_group_loadavg, &load1);
	line_group_add(&line_group_loadavg, &load5);
	line_group_add(&line_group_loadavg, &load15);

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
	struct itimerspec tmout = { { pla.interval_sec, 0 },
				    { pla.interval_sec, 0 } };
	timerfd_settime(timerfd, 0, &tmout, NULL);
	FD_SET(timerfd, &readfds);
	if (maxfd < timerfd)
		maxfd = timerfd;

	FD_SET(sig_rd_fd, &readfds);
	if (maxfd < sig_rd_fd)
		maxfd = sig_rd_fd;

	plot_update_size(&pla);
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
			unsigned char signo;
			const ssize_t cnt = read(sig_rd_fd, &signo, 1);
			if (cnt > 0) {
				if (signo == SIGINT) {
					done = true;
					break;
				} else if (signo == SIGWINCH) {
					endwin();
					initscr();
					erase();
					refresh();
					plot_update_size(&pla);
					redraw = true;
				}
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
