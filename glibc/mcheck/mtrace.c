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
	int *a = malloc(12);
	mtrace();

	a[3] = 14;
	muntrace();
	free(a);
	return 0;
}
