/**
 * zombie - process was exited, but nobody reclaim it.
 */
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "proc_helpers.h"


static struct env {
	int child_sleep_secs;
	int parent_sleep_secs;
	int nr_children;
	int verbose;
} env = {
	.child_sleep_secs = 0,
	.parent_sleep_secs = 60,
	.nr_children = 1,
	.verbose = false,
};

#define LOG_VERBOSE(fmt...) do {	\
		if (!env.verbose)	\
			break;	\
		char ___buf[64];	\
		prctl(PR_GET_NAME, ___buf, 0, 0, 0);	\
		char __state = proc_state();	\
		fprintf(stderr, "[%-16s %-8d %c] ", ___buf, getpid(), __state);	\
		fprintf(stderr, fmt);	\
	} while (0)

static const char argp_prog_doc[] =
	"USAGE: [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "child-sleep-secs", 's', "SECS", 0, "Child sleep seconds, default: 0" },
	{ "parent-sleep-secs", 'S', "SECS", 0, "Parent sleep seconds, default: 60" },
	{ "nr-children", 'n', "NUM", 0, "Number of children, default: 1" },
	{ "verbose", 'v', NULL, 1, "Run with verbose mode" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'S':
		env.parent_sleep_secs = atoi(arg);
		if (env.parent_sleep_secs <= 0) {
			fprintf(stderr, "Bad value of -S.\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 's':
		env.child_sleep_secs = atoi(arg);
		if (env.child_sleep_secs <= 0) {
			fprintf(stderr, "Bad value of -s.\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'n':
		env.nr_children = atoi(arg);
		if (env.nr_children <= 0) {
			fprintf(stderr, "Bad value of -n.\n");
			exit(EXIT_FAILURE);
		}
		break;
	case 'v':
		env.verbose = true;
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
	pid_t child, *children;
	int status, err, i;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	children = malloc(sizeof(pid_t) * env.nr_children);

	for (i = 0; i < env.nr_children; i++) {
		if ((child = fork()) < 0) {
			perror("fork");
			exit(1);
		}

		/* Child exit after sleep */
		if (child == 0) {
			char buf[64];
			snprintf(buf, sizeof(buf) - 1, "zombie-child/%d", i);
			prctl(PR_SET_NAME, buf, 0, 0, 0);

			if (env.child_sleep_secs > 0) {
				for (i = 0; i < env.child_sleep_secs; i++) {
					sleep(1);
					LOG_VERBOSE("sleeping %d s...\n", i + 1);
				}
			}
			LOG_VERBOSE("exit.\n");
			exit(0);
		} else {
			children[i] = child;
		}
	}

	prctl(PR_SET_NAME, "zombie-parent", 0, 0, 0);

	/**
	 * Parent
	 * Gives children time to observe the zombie using ps(1)
	 */
	for (i = 0; i < env.parent_sleep_secs; i++) {
		sleep(1);
		char state = proc_pid_state(child);
		LOG_VERBOSE("sleeping %d s, child state %c.\n", i + 1, state);
	}

	/**
	 * After that, parent wait(2)s its child's exit status, and prints a
	 * relevant message.
	 */
	for (i = 0; i < env.nr_children; i++) {
		child = wait(&status);
		if (WIFEXITED(status))
			LOG_VERBOSE("Process %d exited with status %d.\n",
				    child, WEXITSTATUS(status));
	}

	free(children);

	return 0;
}
