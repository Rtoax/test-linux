#include <stdio.h>
#include <unistd.h>

void ansi(void)
{
	int ansi = isatty(STDOUT_FILENO);
	printf("%s/* This is C comment */%s\n", ansi ? "\033[2m" : "",
	       ansi ? "\033[m" : "");
}

int main(void)
{
	FILE *fp = fopen("tmp.out", "w");

#define P(fd)                                                            \
	printf("%-8s: fd = %4d, tty %s, isatty = %d\n", #fd, fileno(fd), \
	       ttyname(fileno(fd)), isatty(fileno(fd)))

	P(stdin); /* null if 'echo hello | ./isatty' */
	P(stdout);
	P(stderr); /* null if './isatty 2>/dev/null' */
	P(fp);

#undef P

	fclose(fp);

	ansi();

	return 0;
}
