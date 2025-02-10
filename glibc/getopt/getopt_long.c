#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


int command(int argc, char *argv[])
{
	int c;
	/* Flag set by '--verbose'. */
	int verbose_flag;

	/**
	 * This is needed if call getopt() serial times.
	 */
	optarg = NULL;
	optind = opterr = optopt = 0;

	struct option options[] = {
		/* These options set a flag. */
		{"verbose", no_argument, &verbose_flag, 'V'},
		{"brief", no_argument, &verbose_flag, 0},
		/* These options don't set a flag.
		 * We distinguish them by their indices.
		 */
		{"add", no_argument, 0, 'a'},
		{"append", no_argument, 0, 'b'},
		{"create", required_argument, 0, 'c'},
		{"delete", required_argument, 0, 'd'},
		{"file", required_argument, 0, 'f'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	while (1) {
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long(argc, argv, "a:b:c:d:f:hV", options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		printf("c = %c, %d, idx %d\n", c, c, option_index);

		switch (c) {
		case 0:
			/* If this option set a flag, do nothing else now. */
			if (options[option_index].flag != 0)
				break;
			printf("0 option %s", options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;
		case 'a':
			puts("option -a\n");
			break;
		case 'b':
			puts("option -b\n");
			break;
		case 'c':
			printf("option -c with value ‘%s'\n", optarg);
			break;
		case 'd':
			printf("option -d with value ‘%s'\n", optarg);
			break;
		case 'f':
			printf("option -f with value ‘%s'\n", optarg);
			break;
		case 'h':
			printf("option -h --help\n");
			break;
		case '?':
			/* getopt_long already printed an error message. */
			fprintf(stderr, "Unknown option or requires an argument.\n");
			exit(1);
			break;
		default:
			printf("default '%s'\n", optarg);
			break;
		}
	}

	/* Instead of reporting '--verbose'
	 * and '--brief' as they are encountered,
	 * we report the fnal status resulting from them. */
	if (verbose_flag)
		puts("verbose flag is set");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar('\n');
	}

	return 0;
}

int command2(int argc, char *argv[])
{
	return command(argc, argv);
}

int main(int argc, char *argv[], char *envs[])
{
#if defined(INNER_CALL)
	int _argc = 5;
	char *___argv[] = {"cmd", "-c", "ccc", "-d", "ddd"};
	command2(_argc, ___argv);
	return command(argc, argv);
#else
	return command(argc, argv);
#endif
}
