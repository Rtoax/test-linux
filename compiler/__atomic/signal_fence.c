/**
 * void __atomic_signal_fence (int memorder)
 *
 * - Synchronization fence between a thread and signal handlers based in the
 *   same thread.
 * - All memory orders are valid.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>

int a, b;

void handler(int signum)
{
	if (__atomic_load_n(&a, __ATOMIC_ACQUIRE) == 1) {
		__atomic_signal_fence(__ATOMIC_ACQUIRE);
		assert(__atomic_load_n(&b, __ATOMIC_RELAXED) == 1);
	}
	exit(0);
}

int main(void)
{
	signal(SIGTERM, &handler);

	__atomic_store_n(&b, 1, __ATOMIC_RELAXED);
	__atomic_signal_fence(__ATOMIC_RELAXED);
	__atomic_store_n(&a, 1, __ATOMIC_RELAXED);

	return 0;
}
