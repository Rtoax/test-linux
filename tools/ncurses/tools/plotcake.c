// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
/**
 * Plotting data curves in the terminal.
 *
 * The default plot is loadavg, loadavg graph of 1, 5, 15 minutes.
 *
 * see also
 * https://github.com/rtoax/plotcake
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
#include "file.h"
#include "load.h"
#include "keyboard.h"
#include "value.h"
#include "plot.h"
#include "ram.h"
#include "stdin.h"

enum {
	ARG_LOGARITHMIC = 200,
	ARG_LOGARITHMIC10,
	ARG_EXPONENTIAL,
};

const char argp_prog_doc[] = ANSI_BOLD
	"USAGE: " ANSI_RST "[-T|--title=<TITLE>] [-v|--verbose]\n"
	"\n" ANSI_BOLD "EXAMPLES:\n" ANSI_RST "\n" ANSI_GREEN
	"   $ plotcake        " ANSI_RST ANSI_GRAY
	"# Draw loadavg graph\n" ANSI_RST ANSI_GREEN
	"   $ plotcake -M     " ANSI_RST ANSI_GRAY
	"# Draw memory usage graph\n" ANSI_RST "\n"
	"   If data is retrieved from stdin, then \\n will be used as the delimiter\n"
	"   by default, for example:\n"
	"\n"
	"   " ANSI_GRAY "# Draw opened file number\n" ANSI_RST ANSI_GREEN
	"   $ while sleep .5; do\n"
	"	awk '{print $1}' /proc/sys/fs/file-nr\n"
	"     done | plotcake --title 'Opened File Number' -l 'opened'\n" ANSI_RST
	"\n"
	"   " ANSI_GRAY "# Draw one line\n" ANSI_RST ANSI_GREEN
	"   $ seq 1 1 10 | plotcake\n" ANSI_RST "   " ANSI_GRAY
	"# Draw ten line\n" ANSI_RST ANSI_GREEN
	"   $ seq -s=' ' 1 1 10 | plotcake\n" ANSI_RST "\n" ANSI_BOLD
	"SHORTCUT KEY:\n" ANSI_RST "\n"
	"   " KEY_HELP_h "\n"
	"   " KEY_HELP_l "\n"
	"   " KEY_HELP_q "\n"
	"   " KEY_HELP_r "\n"
	"   " KEY_HELP_t "\n"
	"   " KEY_HELP_v "\n"
	"   " KEY_HELP_ENTER "\n"
	"   " KEY_HELP_UP "\n"
	"   " KEY_HELP_DOWN "\n"
	"   " KEY_HELP_LEFT "\n"
	"   " KEY_HELP_RIGHT "\n"
	"\n" ANSI_BOLD "OPTIONS:" ANSI_RST;

static const struct argp_option opts[] = {
	{ "title", 'T', "TITLE", 0, "Specify title" },
	{ "xlabel", 'x', "LABEL", 0, "Specify x axis label" },
	{ "ylabel", 'y', "LABEL", 0, "Specify y axis label" },
	{ "llabel", 'l', "NAME", 0,
	  "Specify line label (may be listed multiple times)" },
	{ "ltype", 'L', "TYPE", 0,
	  "Specify line types, if an invalid value is entered, the supported "
	  "line types will be listed (may be listed multiple times)" },
	{ "lcolor", 'C', "COLOR", 0,
	  "Specify line colors, if an invalid value is entered, the supported "
	  "line colors will be listed, can match color prefixes, such as 'r' "
	  "matching 'red' (may be listed multiple times)" },
	{ "ram", 'M', NULL, 1, "Display memory instead of loadavg" },
	{ "interval", 'I', "SEC", 0,
	  "Specify interval time, the default unit is nanoseconds, but units "
	  "such as 's', 'ms', 'us', and 'ns' can also be used." },
	{ "logarithmic", ARG_LOGARITHMIC, NULL, 1,
	  "Use natural logarithmic (shortcut " KEY_HELP_t ")" },
	{ "logarithmic10", ARG_LOGARITHMIC10, NULL, 1,
	  "Use base-10 logarithmic, the curve shape is exactly the same as "
	  "--logarithmic, only the values of the tick labels on the axes are "
	  "different (shortcut " KEY_HELP_t ")" },
	{ "exponential", ARG_EXPONENTIAL, NULL, 1,
	  "Use base-e exponential (shortcut " KEY_HELP_t ")" },
	{ "tmout", 't', "SEC", 0,
	  "Specify timeout time, the default unit is nanoseconds, but units "
	  "such as 's', 'ms', 'us', and 'ns' can also be used." },
	{ "ofile", 'o', "OFILE", 0,
	  "Specify the output file name, excluding the extension." },
	{ "file", 'f', "FILE", 0,
	  "Specify input file, the format must conform to the plotcake file "
	  "format. You can run plotcake once to view the generated files (txt"
#ifdef HAVE_JSON_C
	  " and json"
#endif
	  ")." },
	{ "verbose", 'v', NULL, 1,
	  "Display detail (shortcut: " KEY_HELP_v ")" },
	{ "version", 'V', NULL, 1, "Display version" },
	{},
};

static int sig_rd_fd, sig_wr_fd;
static int done = false;
static int ram = false;
static int verbose = false;
static unsigned long tmout_nsecs = 0;
static unsigned long interval_nsecs = 1000000000UL;
static char *output_file_prefix = NULL;
static char *file = NULL;
static char *title = NULL;
static char *xlabel = NULL;
static char *ylabel = NULL;

struct plot plot = { 0 };
struct keyboard keyboard = { 0 };

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
		title = arg;
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
		enqueue_lcolor(color_name2num(arg));
		break;
	case 'x':
		xlabel = arg;
		break;
	case 'y':
		ylabel = arg;
		break;
	case 't':
		tmout_nsecs = str2nsecs(arg);
		if (tmout_nsecs == 0) {
			fprintf(stderr, "ERROR: bad -t value\n");
			exit(EXIT_FAILURE);
		}
		break;
	case ARG_LOGARITHMIC:
		plot.v_scaling = NS_LOGARITHMIC;
		break;
	case ARG_EXPONENTIAL:
		plot.v_scaling = NS_EXPONENTIAL;
		break;
	case ARG_LOGARITHMIC10:
		plot.v_scaling = NS_LOGARITHMIC10;
		break;
	case 'I':
		interval_nsecs = str2nsecs(arg);
		if (interval_nsecs == 0) {
			fprintf(stderr, "ERROR: bad -I value\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'M':
		ram = true;
		break;
	case 'f':
		file = strdup(arg);
		break;
	case 'o':
		output_file_prefix = strdup(arg);
		break;
	case 'v':
		verbose = true;
		break;
	case 'V':
		printf("%s %s\n", GIT_REPO, MY_VERSION);
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

static int new_timerfd(unsigned long nsecs)
{
	int timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC);
	unsigned long secs = nsecs / 1000000000UL;
	nsecs -= secs * 1000000000UL;
	struct itimerspec to = { { secs, nsecs }, { secs, nsecs } };
	timerfd_settime(timerfd, 0, &to, NULL);
	return timerfd;
}

int main(int argc, char *argv[])
{
	int err = 0;
	int maxfd = 0;
	int freshtimerfd, keyfd, stdinfd, tmoutfd;
	int sigpipe[2];
	fd_set readfds;
	char stdin_buffer[4096] = { 0 };

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "args parse failed %d\n", err);
		return -err;
	}

	keyboard_init(&keyboard);
	err = plot_init(&plot, &keyboard, file);
	if (err) {
		fprintf(stderr, "plot init failed, %s\n", strerror(-err));
		return err;
	}

	setlocale(LC_ALL, "");

	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);

	if (pipe(sigpipe) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	sig_rd_fd = sigpipe[0];
	sig_wr_fd = sigpipe[1];

	tmoutfd = freshtimerfd = keyfd = stdinfd = -1;

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
		stdinfd = STDIN_FILENO;
	} else
		keyfd = STDIN_FILENO;

	FD_SET(keyfd, &readfds);
	if (maxfd < keyfd)
		maxfd = keyfd;

	if (stdinfd != -1) {
		FD_SET(stdinfd, &readfds);
		if (maxfd < stdinfd)
			maxfd = stdinfd;
	} else if (!file) {
		/**
		 * Not create fresh timer if read data from file.
		 *
		 * Note: When we read data from stdin, we no longer need this
		 * timer to trigger the update.
		 */
		freshtimerfd = new_timerfd(interval_nsecs);
		FD_SET(freshtimerfd, &readfds);
		if (maxfd < freshtimerfd)
			maxfd = freshtimerfd;
	}

	if (tmout_nsecs != 0) {
		tmoutfd = new_timerfd(tmout_nsecs);
		FD_SET(tmoutfd, &readfds);
		if (maxfd < tmoutfd)
			maxfd = tmoutfd;
	}

	FD_SET(sig_rd_fd, &readfds);
	if (maxfd < sig_rd_fd)
		maxfd = sig_rd_fd;

	/* curses start from here */

	/**
	 * In ncurses, the biggest difficulty in detecting a single press of the
	 * Esc key directly is that the Esc key, besides being a key itself, is
	 * also the starting byte of all escape sequences (such as arrow keys).
	 *
	 * To avoid confusion, ncurses, upon detecting the Esc key, briefly
	 * waits to see if there are any subsequent characters. This process
	 * (usually about 1 second) causes a sense of 'delay'.
	 *
	 * Another method is to set the environment variable with the same name,
	 * ESCDELAY=50.
	 */
	set_escdelay(50);

	initscr();
	cbreak();
	noecho();
	nonl();

	curs_set(0);

	/* make wgetch() return KEY_xxx, and non-blocking */
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	init_flavor();

	if (stdinfd == -1) {
		if (!file && ram) {
			plot.title = plot.title ?: (title ?: "Memory Usage");
			plot.label_x = plot.label_x ?: (xlabel ?: "Time");
			plot.label_y = plot.label_y ?: (ylabel ?: "Size(MB)");
			plot_add_lgroup(&plot, &lg_ram, NULL);
		} else if (!file) {
			plot.title = plot.title ?: (title ?: "Loadavg");
			plot.label_x = plot.label_x ?: (xlabel ?: "Time");
			plot.label_y = plot.label_y ?: (ylabel ?: "Load");
			plot_add_lgroup(&plot, &lg_loadavg, NULL);
		}
	} else {
		struct stdin_arg stdarg = {
			.nline = 1, /* at least one line */
			.line_buff = stdin_buffer,
		};
		plot.title = plot.title ?: (title ?: "stdin");
		plot.label_x = plot.label_x ?: (xlabel ?: "Time");
		plot.label_y = plot.label_y ?: (ylabel ?: "Value");
		plot_add_lgroup(&plot, &lg_stdin, &stdarg);
	}

	/* Read from 'file' instead of create()/update() */
	if (!file) {
		plot_create_data(&plot);
		plot_update_data(&plot);
	}
	plot_update_size(&plot, true);
	plot_redraw(&plot, verbose);

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
					case 0x445b1b:
						key = KEY_LEFT;
						break;
					case 0x434f1b:
					case 0x435b1b:
						key = KEY_RIGHT;
						break;
					case 0x424f1b:
					case 0x425b1b:
						key = KEY_DOWN;
						break;
					case 0x414f1b:
					case 0x415b1b:
						key = KEY_UP;
						break;
					default:
						/* Handle more here */
						break;
					}
					plot.kb->current_key = key;
				} else {
					plot.kb->current_key = ERR;
				}
			/**
			 * keyfd = STDIN_FILENO
			 */
			} else {
				/* need keypad() and nodelay() */
				plot.kb->current_key = wgetch(stdscr);
				count = 1;
			}

			if (plot.kb->current_key != ERR) {
				plot.kb->cnt.total += count;
				switch (plot.kb->current_key) {
				case KEY_LEFT:
					plot.kb->cnt.left++;
					redraw = true;
					break;
				case KEY_RIGHT:
					plot.kb->cnt.right++;
					redraw = true;
					break;
				case KEY_UP:
					plot.kb->cnt.up++;
					plot_scaling_up(&plot);
					redraw = true;
					break;
				case KEY_DOWN:
					plot.kb->cnt.down++;
					plot_scaling_down(&plot);
					redraw = true;
					break;
				case 'q': /* quit */
				case 27: /* Esc */
					broadcast_sig(SIGINT);
					goto end;
					break;
				case 'v': /* verbose mode switch */
					plot.kb->cnt.v++;
					redraw = true;
					verbose = !verbose;
					break;
				case 'r': /* reset plot */
					plot.kb->cnt.r++;
					redraw = true;
					break;
				case 't': /* select numerical scaling type */
					plot.kb->cnt.t++;
					redraw = true;
					plot.v_scaling =
						(plot.v_scaling + 1) % NS_MAX;
					break;
				case 'h': /* help */
					plot.kb->cnt.h++;
					redraw = true;
					break;
				case 'l': /* list line labels */
					plot.kb->cnt.l++;
					redraw = true;
					break;
				case 13: /* enter */
					plot.kb->cnt.enter++;
					redraw = true;
					break;
				}
			}
		} else if (ret > 0 && FD_ISSET(freshtimerfd, &fds)) {
			uint64_t exp;
			read(freshtimerfd, &exp, sizeof(exp));
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
		} else if (ret > 0 && stdinfd != -1 &&
			   FD_ISSET(stdinfd, &fds)) {
			memset(stdin_buffer, 0, sizeof(stdin_buffer));
			ssize_t cnt = read(stdinfd, stdin_buffer,
					   sizeof(stdin_buffer));
			if (cnt > 0) {
				redraw = true;
			}
			plot_update_data(&plot);
		} else
			continue;

		if (redraw)
			plot_redraw(&plot, verbose);
	}

end:
	if (stdinfd != -1)
		close(stdinfd);
	if (freshtimerfd != -1)
		close(freshtimerfd);
	if (tmoutfd != -1)
		close(tmoutfd);
	if (keyfd != STDIN_FILENO && keyfd != -1)
		close(keyfd);
	close(sig_rd_fd);
	close(sig_wr_fd);
	endwin();

	if (file)
		free(file);

	if (verbose) {
		struct plot *_p = &plot;
		fprintf(stderr, PLOT_INF0_FMT "\n", PLOT_INF0_ARG(_p));
		fprintf(stderr, KEYBOARD_INF0_FMT "\n",
			KEYBOARD_INF0_ARG(_p->kb));
	}
	save_plot(&plot, output_file_prefix);
	if (output_file_prefix)
		free(output_file_prefix);
	return 0;
}
