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
#include "load.h"
#include "value.h"
#include "plot.h"
#include "ram.h"
#include "stdin.h"

enum {
	ARG_LOGARITHMIC = 200,
	ARG_LOGARITHMIC10,
};

const char argp_prog_doc[] =
	"USAGE: [-T|--title=<TITLE>] [-v|--verbose]\n"
	"\n"
	"EXAMPLES:\n"
	"\n"
	"   $ ./plotcake        # Draw loadavg graph\n"
	"   $ ./plotcake -M     # Draw memory usage graph\n"
	"\n"
	"   # Draw opened file number\n"
	"   $ while sleep .5; do\n"
	"	awk '{print $1}' /proc/sys/fs/file-nr\n"
	"     done | ./plotcake --title 'Opened File Number' -l 'opened'\n"
	"\n"
	"SHORTCUT KEY:\n"
	"\n"
	"   'q', Esc: quit\n"
	"\n"
	"OPTIONS:\n";

static const struct argp_option opts[] = {
	{ "title", 'T', "TITLE", 0, "Spedify title" },
	{ "xlabel", 'x', "X LABEL", 0, "Spedify x axis label" },
	{ "ylabel", 'y', "Y LABEL", 0, "Spedify y axis label" },
	{ "llabel", 'l', "LINE NAME", 0,
	  "Spedify line label (may be listed multiple times)" },
	{ "ltype", 'L', "LINE TYPE", 0,
	  "Spedify line types, if an invalid value is entered, the supported line types will be listed (may be listed multiple times)" },
	{ "lcolor", 'C', "LINE COLOR", 0,
	  "Spedify line colors, if an invalid value is entered, the supported line colors will be listed, can match color prefixes, such as 'r' matching 'red' (may be listed multiple times)" },
	{ "ram", 'M', NULL, 1, "Display memory instead of loadavg" },
	{ "interval", 'I', "INTERVAL SEC", 0, "Spedify interval seconds" },
	{ "logarithmic", ARG_LOGARITHMIC, NULL, 1, "Use natural logarithmic" },
	{ "logarithmic10", ARG_LOGARITHMIC10, NULL, 1,
	  "Use base-10 logarithmic, the curve shape is exactly the same as --logarithmic, only the values of the tick labels on the axes are different." },
	{ "tmout", 't', "TIMEOUT SEC", 0, "Spedify timeout seconds" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{ "version", 'V', NULL, 1, "Display version" },
	{},
};

static int sig_rd_fd, sig_wr_fd;
static int done = false;
static int ram = false;
static int verbose = false;
static int tmout_sec = -1;
static int interval_sec = 1;

static char data_from_stdin[256] = { 0 };

struct plot plot = {
	.title = NULL,
	.logarithmic = T_NONE,
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

static error_t parse_arg(int opt, char *arg, struct argp_state *state)
{
	switch (opt) {
	case 'T':
		plot.title = arg;
		break;
	case 'l':
		enqueue_llabel(arg);
		break;
	case 'L':
		if (!ldraw_hasname(arg))
			exit(EXIT_FAILURE);
		enqueue_ltype(ldraw_name2type(arg));
		break;
	case 'C':
		if (!hascolor_name(arg))
			exit(EXIT_FAILURE);
		enqueue_lcolor(color_name2n(arg));
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
	case ARG_LOGARITHMIC:
		plot.logarithmic = T_LOGARITHMIC;
		break;
	case ARG_LOGARITHMIC10:
		plot.logarithmic = T_LOGARITHMIC10;
		break;
	case 'I':
		interval_sec = atoi(arg);
		if (interval_sec <= 0) {
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
	case 'V':
		printf("%s\n", MY_VERSION);
		exit(EXIT_SUCCESS);
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
	 * device to read the keyboard. for example:
	 *
	 *   $ while sleep 1; echo 1; done | plotcake
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
		struct itimerspec to = { { interval_sec, 0 },
					 { interval_sec, 0 } };
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

	/* make wgetch() return KEY_xxx, and non-blocking */
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

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

	plot_create_data(&plot);
	plot_update_size(&plot, true);
	plot_update_data(&plot);
	plot_redraw(&plot);

	/* main loop */
	while (!done) {
		fd_set fds = readfds;
		bool redraw = false;

		int ret = select(maxfd + 1, &fds, NULL, NULL, NULL);
		if (ret > 0 && FD_ISSET(keyfd, &fds)) {
			int count = 0;
			/**
			 * keyfd = open("/dev/tty")
			 */
			if (keyfd != STDIN_FILENO) {
				int key = 0;
				count = read(keyfd, &key, sizeof(key));
				if (count > 0) {
					/* convert to ncurses KEY */
					switch (key) {
					case 0x444f1b:
						key = KEY_LEFT;
						break;
					case 0x434f1b:
						key = KEY_RIGHT;
						break;
					case 0x424f1b:
						key = KEY_DOWN;
						break;
					case 0x414f1b:
						key = KEY_UP;
						break;
					default:
						/* Handle more here */
						break;
					}
					plot.keyboard.key = key;
				} else {
					plot.keyboard.key = ERR;
				}
			/**
			 * keyfd = STDIN_FILENO
			 */
			} else {
				/* need keypad() and nodelay() */
				plot.keyboard.key = wgetch(stdscr);
				count = 1;
			}

			if (plot.keyboard.key != ERR) {
				plot.keyboard.count += count;
				switch (plot.keyboard.key) {
				case 'q':
				case 27: /* Esc */
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
			plot_redraw(&plot);
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
