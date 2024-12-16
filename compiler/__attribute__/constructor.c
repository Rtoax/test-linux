#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
 * Note: attribute constructor and destructor is works in both dynamic and
 * static libraries.
 *
 * Execute procedure: _start() -> ctors -> main() -> dtors
 */

#define debug() do { \
		printf("[%s:%s %d]\n", __FILE__, __func__, __LINE__); \
	} while(0)

void sig_handler(int signo)
{
	printf("Catch signal.\n");
	exit(1);
}

void __attribute__((constructor)) before(void)
{
	debug();
}
void __attribute__((constructor(101))) before1(void)
{
	debug();
}
void __attribute__((constructor(102))) before2(void)
{
	debug();
}

void __attribute__((destructor)) after(void)
{
	debug();
}
void __attribute__((destructor(101))) after1(void)
{
	debug();
}
void __attribute__((destructor(101))) after2(void)
{
	debug();
}

int main(void)
{
	signal(SIGINT, sig_handler);

	debug();
	raise(SIGINT);
	/**
	 * The dtor still running after main
	 */
	exit(1);
	return 0;
}
