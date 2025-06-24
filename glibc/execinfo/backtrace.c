#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#define BACKTRACE_SIZE	1024

/* Obtain a backtrace and print it to stdout. */
void print_trace(void)
{
	void *array[BACKTRACE_SIZE];
	size_t size;
	char **symbols;
	size_t i;

	size = backtrace(array, BACKTRACE_SIZE);
	symbols = backtrace_symbols(array, size);

	FILE *fp = fopen("core.coredump", "w");
	backtrace_symbols_fd(array, size, fileno(fp));
	fclose(fp);

	printf("Obtained %zd stack frames.\n", size);
	for (i = 0; i < size; i++)
		printf("%p -> %s\n", array[i], symbols[i]);

	free(symbols);
}

/* A dummy function to make the backtrace more interesting. */
void dummy_function(void)
{
	print_trace();
}

int main(void)
{
	dummy_function();
	return 0;
}
