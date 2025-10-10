/**
 * zombie - process was exited, but nobody reclaim it.
 */
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


static struct env {
	int parent_sleep_secs;
	int verbose;
} env = {
	.parent_sleep_secs = 60,
	.verbose = false,
};

static const char argp_prog_doc[] =
	"USAGE: [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "parent-sleep-secs", 'S', "SECS", 0, "Parent sleep seconds, default: 60" },
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
	pid_t pid;
	int status, err;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	/* Child exit immediatly */
	if (pid == 0)
		exit(0);

	/**
	 * Parent
	 * Gives children time to observe the zombie using ps(1)
	 */
	sleep(env.parent_sleep_secs);

	/**
	 * After that, parent wait(2)s its child's exit status, and prints a
	 * relevant message.
	 */
	pid = wait(&status);
	if (WIFEXITED(status))
		fprintf(stderr, "\n\t[%d]\tProcess %d exited with status %d.\n",
				(int)getpid(), pid, WEXITSTATUS(status));

	return 0;
}
