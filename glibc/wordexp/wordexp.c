#include <stdio.h>
#include <stdlib.h>
#include <wordexp.h>

int main(void)
{
	wordexp_t p;
	char **w;

	wordexp("[a-z]*.c", &p, 0);
	w = p.we_wordv;
	for (size_t i = 0; i < p.we_wordc; i++)
		printf("%s\n", w[i]);
	wordfree(&p);
	exit(EXIT_SUCCESS);
}
