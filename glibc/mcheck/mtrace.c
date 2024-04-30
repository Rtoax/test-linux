#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mcheck.h>
#include <signal.h>

static void enable(int sig)
{
	mtrace();
	signal(SIGUSR1, enable);
}
static void disable(int sig)
{
	muntrace();
	signal(SIGUSR2, disable);
}

int main(void)
{
	int *a;

	setenv("MALLOC_TRACE", "./mtrace.log", 1);

	mtrace();

	a = malloc(12);
	a[3] = 14;
	free(a);

	muntrace();

	return 0;
}
