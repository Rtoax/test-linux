/**
 * type __atomic_load_n (type *ptr, int memorder)
 * void __atomic_load (type *ptr, type *ret, int memorder)
 *
 * valid memory order variants:
 * - __ATOMIC_RELAXED
 * - __ATOMIC_SEQ_CST
 * - __ATOMIC_ACQUIRE
 * - __ATOMIC_CONSUME
 *
 * void __atomic_store_n (type *ptr, type val, int memorder)
 * void __atomic_store (type *ptr, type *val, int memorder)
 *
 * valid memory order variants:
 * - __ATOMIC_RELAXED
 * - __ATOMIC_SEQ_CST
 * - __ATOMIC_RELEASE
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

volatile int x, y, a, b;

#if defined(TEST_C_RAW)
void *task1(void *arg)
{
	a = 1;
	x = b;
	pthread_exit(NULL);
}

void *task2(void *arg)
{
	b = 1;
	y = a;
	pthread_exit(NULL);
}
#elif defined(TEST_ATOMIC_RELAXED)
/**
 * This does not solve the out-of-order problem
 */
void *task1(void *arg)
{
	__atomic_store_n(&a, 1, __ATOMIC_RELAXED);
	__atomic_store_n(&x, __atomic_load_n(&b, __ATOMIC_RELAXED), __ATOMIC_RELAXED);
	pthread_exit(NULL);
}

void *task2(void *arg)
{
	__atomic_store_n(&b, 1, __ATOMIC_RELAXED);
	__atomic_store_n(&y, __atomic_load_n(&a, __ATOMIC_RELAXED), __ATOMIC_RELAXED);
	pthread_exit(NULL);
}
#elif defined(TEST_ATOMIC_STRICT)
/**
 * __ATOMIC_SEQ_CST like rw barrier
 */
void *task1(void *arg)
{
	__atomic_store_n(&a, 1, __ATOMIC_SEQ_CST);
	__atomic_store_n(&x, __atomic_load_n(&b, __ATOMIC_SEQ_CST), __ATOMIC_SEQ_CST);
	pthread_exit(NULL);
}

void *task2(void *arg)
{
	__atomic_store_n(&b, 1, __ATOMIC_SEQ_CST);
	__atomic_store_n(&y, __atomic_load_n(&a, __ATOMIC_SEQ_CST), __ATOMIC_SEQ_CST);
	pthread_exit(NULL);
}
#endif

int main(void)
{
	size_t count = 0;
	pthread_t tasks[2];

	while (true) {
		x = y = a = b = 0;
		count++;

		pthread_create(&tasks[0], NULL, task1, NULL);
		pthread_create(&tasks[1], NULL, task2, NULL);

		pthread_join(tasks[0], NULL);
		pthread_join(tasks[1], NULL);

		if (x == 0 && y == 0) {
			fprintf(stderr, "WARNING: CPU Out of Order Exec.\n");
			break;
		}

		if (count % 1000 == 0)
			fprintf(stderr, "Test count %ld\n", count);
	}

	fprintf(stderr, "Total test count %ld\n", count);

	return 0;
}
