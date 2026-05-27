// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
/**
 * Plot and disploty a loadavg graph of 1, 5, 15 minutes in the Linux terminal
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
#include <fcntl.h>
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
#include "ram.h"
#include "plot.h"
#include "stdin.h"

const char argp_prog_doc[] = "USAGE: [-T|--title=<TITLE>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "title", 'T', "TITLE", 0, "Spedify title" },
	{ "ram", 'M', NULL, 1, "Display memory instead of loadavg" },
	{ "interval", 'I', "INTERVAL SEC", 0, "Spedify interval seconds" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

static int sig_rd_fd, sig_wr_fd;
static char key = ' ';
static int done = false;
static int ram = false;
static int verbose = false;

static char data_from_stdin[256];

struct plot plot = {
	.title = "Load average",
	.interval_sec = 1,
};

void sig_handler(int signo)
{
	int ret, saved_errno = errno;
	do {
		ret = write(sig_wr_fd, &signo, 1);
	} while ((ret == -1) && (errno == EINTR));
	errno = saved_errno;
}

static void loadavg_create(struct lgroup *lg, void *arg)
{
	new_line(lg, "load1", C_RED);
	new_line(lg, "load5", C_GREEN);
	new_line(lg, "load15", C_BLUE);
}

static void loadavg_update(struct lgroup *lg, void *arg)
{
	double avg[3];

	getloadavg(avg, 3);

	int i = 0;
	for_each_line(lg, line)
	{
		plot_append_val(lg->plot, line, avg[i]);
#ifdef DEBUG
		mvprintw(i + 1, BND_LEFT + 1, "- %d - %f - %lf~%lf",
			 line->count, avg[i], line->min->v, line->max->v);
#endif
		i++;
	}
#ifdef DEBUG
	mvprintw(i + 1, BND_LEFT + 1, "- %s", data_from_stdin);

	mvprintw(lg->plot->height - BND_BOTTOM + 2, BND_LEFT + 1,
		 "%.2f %.2f %.2f, row %d (%d), col %d (%d), key '%d=%c'\n",
		 avg[0], avg[1], avg[2], LINES, lg->plot->plotheight, COLS,
		 lg->plot->plotwidth, key, key);
#endif
}

static const struct lgroup_operations loadavg_ops = {
	.create = loadavg_create,
	.update = loadavg_update,
};

static struct lgroup lg_loadavg = {
	.ops = loadavg_ops,
};

static error_t parse_arg(int opt, char *arg, struct argp_state *state)
{
	switch (opt) {
	case 'T':
		plot.title = arg;
		break;
	case 'I':
		plot.interval_sec = atoi(arg);
		if (plot.interval_sec <= 0) {
			fprintf(stderr, "ERROR: bad -I value\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'M':
		ram = true;
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
	int maxfd = 0;
	int timerfd, keyfd, datafd;
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

	timerfd = keyfd = datafd = -1;

	FD_ZERO(&readfds);

	/**
	 * If stdin is redirected, open the terminal for key press.
	 *
	 * When we use stdin to pass data, we need to directly open the tty
	 * device to read the keyboard.
	 */
	if (!isatty(STDIN_FILENO)) {
		keyfd = open("/dev/tty", O_RDONLY);
		if (keyfd == -1) {
			fprintf(stderr, "ERROR: open /dev/tty failed, %m\n");
			exit(EXIT_FAILURE);
		}
		datafd = STDIN_FILENO;
	} else
		keyfd = STDIN_FILENO;

	FD_SET(keyfd, &readfds);
	if (maxfd < keyfd)
		maxfd = keyfd;

	if (datafd != -1) {
		FD_SET(datafd, &readfds);
		if (maxfd < datafd)
			maxfd = datafd;
	} else {
		/**
		 * When we read data from stdin, we no longer need a timer to
		 * trigger the update.
		 */
		timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
		struct itimerspec tmout = { { plot.interval_sec, 0 },
					    { plot.interval_sec, 0 } };
		timerfd_settime(timerfd, 0, &tmout, NULL);
		FD_SET(timerfd, &readfds);
		if (maxfd < timerfd)
			maxfd = timerfd;
	}

	FD_SET(sig_rd_fd, &readfds);
	if (maxfd < sig_rd_fd)
		maxfd = sig_rd_fd;

	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);

	/* curses start from here */

	initscr();
	cbreak();
	noecho();
	nonl();

	curs_set(0);

	init_flavor();

	if (datafd == -1) {
		if (ram) {
			plot.title = "Memory Usage";
			plot_add(&plot, &lg_ram, NULL);
		} else
			plot_add(&plot, &lg_loadavg, NULL);
	} else {
		struct stdin_arg stdarg = {
			.nline = 2,
			.line_buff = data_from_stdin,
		};
		plot_add(&plot, &lg_stdin, &stdarg);
	}

	for_each_lg(&plot, lg)
	{
		lg->ops.create(lg, NULL);
	}

	plot_update_size(&plot);
	redraw_screen(&plot);

	/* main loop */
	while (!done) {
		fd_set fds = readfds;
		bool redraw = false;

		int ret = select(maxfd + 1, &fds, NULL, NULL, NULL);
		if (ret > 0 && FD_ISSET(keyfd, &fds)) {
			int count = read(keyfd, &key, 1);
			if (count == 1) {
				switch (key) {
				case 'q':
					goto end;
					break;
				case 13: /* enter */
					redraw = true;
					break;
				}
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
					plot_update_size(&plot);
					redraw = true;
				}
			}
		} else if (ret > 0 && datafd != -1 && FD_ISSET(datafd, &fds)) {
			memset(data_from_stdin, 0, sizeof(data_from_stdin));
			ssize_t cnt = read(datafd, data_from_stdin,
					   sizeof(data_from_stdin));
			if (cnt > 0) {
				/* TODO: parse data and plot */
				redraw = true;
			}
		} else
			continue;

		if (redraw)
			redraw_screen(&plot);
	}

end:
	endwin();
	return 0;
}
