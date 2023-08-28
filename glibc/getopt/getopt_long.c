#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


int main(int argc, char *argv[])
{
	int c;

	/* Flag set by ‘--verbose'. */
	static int verbose_flag;
	static struct option options[] = {
		/* These options set a ﬂag. */
		{"verbose", no_argument, &verbose_flag, 1},
		{"brief", no_argument, &verbose_flag, 0},
		/* These options don't set a ﬂag.
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

		c = getopt_long(argc, argv, "a:b:c:d:f:h", options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
		case 0:
			/* If this option set a ﬂag, do nothing else now. */
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
			break;
		default:
			abort();
		}
	}

	/* Instead of reporting ‘--verbose'
		and ‘--brief' as they are encountered,
		we report the fnal status resulting from them. */
	if (verbose_flag)
		puts ("verbose flag is set");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar('\n');
	}

	return 0;
}