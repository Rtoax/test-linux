/**
 * Test __atomic routines for existence and proper execution on 16 byte
 * values with each valid memory model.
 */
#include <stdio.h>
#include <stdint.h>

extern void abort(void);

int64_t v, count;

int main(void)
{
	v = 0;
	count = 0;

	if (__atomic_load_n(&v, __ATOMIC_RELAXED) != count++)
		abort();
	else
		v++;

	if (__atomic_load_n(&v, __ATOMIC_ACQUIRE) != count++)
		abort();
	else
		v++;

	if (__atomic_load_n(&v, __ATOMIC_CONSUME) != count++)
		abort();
	else
		v++;

	if (__atomic_load_n(&v, __ATOMIC_SEQ_CST) != count++)
		abort();
	else
		v++;

	/* Now test the generic variants. */

	__atomic_load(&v, &count, __ATOMIC_RELAXED);
	if (count != v)
		abort();
	else
		v++;

	__atomic_load(&v, &count, __ATOMIC_ACQUIRE);
	if (count != v)
		abort();
	else
		v++;

	__atomic_load(&v, &count, __ATOMIC_CONSUME);
	if (count != v)
		abort();
	else
		v++;

	__atomic_load(&v, &count, __ATOMIC_SEQ_CST);
	if (count != v)
		abort();
	else
		v++;

	printf("count = %ld\n", count);
	printf("v = %ld\n", v);

	return 0;
}

