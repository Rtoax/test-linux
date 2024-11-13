/**
 * type __sync_lock_test_and_set (type *ptr, type value, ...)
 *
 * - This builtin, as described by Intel;
 * - is not a traditional test-and-set operation, but rather an atomic exchange operation.
 * - It writes value into *ptr, and returns the previous contents of *ptr.
 *
 * void __sync_lock_release (type *ptr, ...)
 *
 * - This builtin releases the lock acquired by __sync_lock_test_and_set.
 * - Normally this means writing the constant 0 to *ptr.
 * - This builtin is not a full barrier, but rather a release barrier.
 * - This means that all previous memory stores are globally visible, and all
 *   previous memory loads have been satisfied, but following memory reads are
 *   not prevented from being speculated to before the barrier.
 */
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	int a, ret;

	a = 10;
	ret = __sync_lock_test_and_set(&a, 20);
	printf("a = %d, ret = %d\n", a, ret);

	__sync_lock_release(&a);
	printf("a = %d\n", a);

	return 0;
}
