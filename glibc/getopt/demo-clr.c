#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


void stty_sane(void)
{
	system("stty sane");
}

void clear(void)
{
	system("clear");
}

void reset(void)
{
	system("reset");
}

void help(void)
{
	printf("\n");
	printf("\033[1mclr\033[m clear the tty.\n\n");
	printf("\033[1mUsage: clr [OPTION...] \033[m \n\n");
	printf("   -s, --sane                   stty sane\n");
	printf("   -c, --clear                  clear\n");
	printf("   -r, --reset                  reset\n");
	printf("   -v, --version                show version\n");
	printf("   -h, --help                   help\n\n");
	printf("Mandatory or optional arguments to long options are also mandatory or optional\n");
	printf("for any corresponding short options.\n");
}

void version(void)
{
	printf("clr 1.0.0 rtoax\n");
}

int main(int argc, char *argv[])
{
	int c;
	static struct option options[] = {
		/* These options set a ﬂag. */
		{"version", no_argument, 0, 'v'},
		{"sane", no_argument, 0, 's'},
		{"clear", no_argument, 0, 'c'},
		{"reset", no_argument, 0, 'r'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	while (1) {
		/* getopt_long stores the option index here. */
		int option_index = 0;
		c = getopt_long(argc, argv, "vscrh", options, &option_index);
		if (c == -1)
			break;
		switch (c) {
		case 's':
			stty_sane();
			break;
		case 'c':
			clear();
			break;
		case 'r':
			reset();
			break;
		case 'h':
			help();
			break;
		case 'v':
			version();
			break;
		default:
			return 1;
		}
	}
	return 0;
}
