// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
/**
 * Plotting data curves in the terminal.
 *
 * The default plot is loadavg, loadavg graph of 1, 5, 15 minutes.
 *
 * see also
 * https://github.com/rtoax/ncurses-tools
 * https://github.com/rtoax/test-linux scripts/loadavg.sh
 *
 * relative repository:
 * ttyplot: https://github.com/tenox7/ttyplot.git
 *          ttyplot is not good enough, I don't like his drawing style.
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
	{ "xlabel", 'x', "X LABEL", 0, "Spedify x axis label" },
	{ "ylabel", 'y', "Y LABEL", 0, "Spedify y axis label" },
	{ "lname", 'l', "LINE NAME", 0,
	  "Spedify line names (may be listed multiple times)" },
	{ "ram", 'M', NULL, 1, "Display memory instead of loadavg" },
	{ "interval", 'I', "INTERVAL SEC", 0, "Spedify interval seconds" },
	{ "tmout", 't', "TIMEOUT SEC", 0, "Spedify timeout seconds" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{},
};

static int sig_rd_fd, sig_wr_fd;
static char key = ' ';
static int done = false;
static int ram = false;
static int verbose = false;
static int tmout_sec = -1;

static char data_from_stdin[256] = { 0 };

struct plot plot = {
	.title = NULL,
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

/**
 * send to every process in the process group of the calling process, to make
 * sure the process preceding the pipeline exits.
 */
void broadcast_sig(int signo)
{
	kill(0, signo);
}

static void loadavg_create(struct lgroup *lg, void *arg)
{
	new_line(lg, "load1", C_RED, &unicode_bold_line_ops);
	new_line(lg, "load5", C_GREEN, &unicode_bold_line_ops);
	new_line(lg, "load15", C_BLUE, &unicode_bold_line_ops);
}

static void loadavg_update(struct lgroup *lg, void *arg)
{
	double avg[3];

	getloadavg(avg, 3);
#ifdef DEBUG
	struct plot *p = lg->plot;
#endif

	int i = 0;
	for_each_line(lg, line)
	{
		line_add(line, avg[i]);
#ifdef DEBUG
		mvprintw(i + 1, p->bnd.left + 1, "- %d - %f - %lf~%lf",
			 line->count, avg[i], line->min->v, line->max->v);
#endif
		i++;
	}
#ifdef DEBUG
	mvprintw(i + 1, p->bnd.left + 1, "- %s", data_from_stdin);

	mvprintw(p->height - p->bnd.bottom + 2, p->bnd.left + 1,
		 "%.2f %.2f %.2f, row %d (%d), col %d (%d), key '%d=%c'\n",
		 avg[0], avg[1], avg[2], LINES, p->plotheight, COLS,
		 p->plotwidth, key, key);
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
	case 'l':
		enqueue_lname(arg);
		break;
	case 'x':
		plot.label_x = arg;
		break;
	case 'y':
		plot.label_y = arg;
		break;
	case 't':
		tmout_sec = atoi(arg);
		if (tmout_sec <= 0) {
			fprintf(stderr, "ERROR: bad -t value\n");
			exit(EXIT_FAILURE);
		}
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
	int timerfd, keyfd, datafd, tmoutfd;
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

	tmoutfd = timerfd = keyfd = datafd = -1;

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
		/**
		 * If stdin is used to transfer data, then the refresh interval
		 * is unnecessary and must be set to 0 so that it can pass the
		 * check in the redraw_screen() function.
		 */
		plot.interval_sec = 0;
	} else {
		/**
		 * When we read data from stdin, we no longer need a timer to
		 * trigger the update.
		 */
		timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
		struct itimerspec to = { { plot.interval_sec, 0 },
					 { plot.interval_sec, 0 } };
		timerfd_settime(timerfd, 0, &to, NULL);
		FD_SET(timerfd, &readfds);
		if (maxfd < timerfd)
			maxfd = timerfd;
	}

	if (tmout_sec != -1) {
		tmoutfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
		struct itimerspec to = { { tmout_sec, 0 }, { tmout_sec, 0 } };
		timerfd_settime(tmoutfd, 0, &to, NULL);
		FD_SET(tmoutfd, &readfds);
		if (maxfd < tmoutfd)
			maxfd = tmoutfd;
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
			plot.title = plot.title ?: "Memory Usage";
			plot.label_x = plot.label_x ?: "Time";
			plot.label_y = plot.label_y ?: "Size(MB)";
			plot_add(&plot, &lg_ram, NULL);
		} else {
			plot.title = plot.title ?: "Loadavg";
			plot.label_x = plot.label_x ?: "Time";
			plot.label_y = plot.label_y ?: "Load";
			plot_add(&plot, &lg_loadavg, NULL);
		}
	} else {
		struct stdin_arg stdarg = {
			.nline = 1, /* at least one line */
			.line_buff = data_from_stdin,
		};
		plot.title = plot.title ?: "stdin";
		plot.label_x = plot.label_x ?: "Time";
		plot.label_y = plot.label_y ?: "Value";
		plot_add(&plot, &lg_stdin, &stdarg);
	}

	for_each_lg(&plot, lg)
	{
		lg->ops.create(lg, lg->ops.arg);
	}

	plot_update_size(&plot, true);
	plot_update_data(&plot);
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
					broadcast_sig(SIGINT);
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
			plot_update_data(&plot);
		} else if (ret > 0 && FD_ISSET(tmoutfd, &fds)) {
			uint64_t exp;
			read(tmoutfd, &exp, sizeof(exp));
			broadcast_sig(SIGINT);
			goto end;
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
					plot_update_size(&plot, false);
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
			plot_update_data(&plot);
		} else
			continue;

		if (redraw)
			redraw_screen(&plot);
	}

end:
	if (datafd != -1)
		close(datafd);
	if (timerfd != -1)
		close(timerfd);
	if (tmoutfd != -1)
		close(tmoutfd);
	if (keyfd != STDIN_FILENO && keyfd != -1)
		close(keyfd);
	close(sig_rd_fd);
	close(sig_wr_fd);
	endwin();
	return 0;
}
