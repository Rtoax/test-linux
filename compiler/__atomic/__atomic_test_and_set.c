/**
 * bool __atomic_test_and_set (void *ptr, int memorder)
 *
 * - performs an atomic test-and-set operation on the byte at *ptr.
 * - It should be only used for operands of type bool or char.
 * - For other types only part of the value may be set.
 * - All memory orders are valid.
 *
 * void __atomic_clear (bool *ptr, int memorder)
 *
 * - After the operation, *ptr contains 0.
 * - valid order are __ATOMIC_RELAXED, __ATOMIC_SEQ_CST, and __ATOMIC_RELEASE.
 */
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	int a, ret;
	char *rslt = "Unknown";
	int order;

	order = __ATOMIC_RELAXED;

	rslt = "Success";
	a = 0;
	ret = __atomic_test_and_set(&a, order);
	if (!a || ret != 0)
		rslt = "Failed";
	printf("a = %d, ret = %d <%s>\n", a, ret, rslt);

	a = 1;
	ret = __atomic_test_and_set(&a, order);
	if (!a || ret != 1)
		rslt = "Failed";
	printf("a = %d, ret = %d <%s>\n", a, ret, rslt);

	a = 10;
	ret = __atomic_test_and_set(&a, order);
	if (!a || ret != 10)
		rslt = "Failed";
	printf("a = %d, ret = %d <%s>\n", a, ret, rslt);

	__atomic_clear(&a, order);
	printf("a = %d (clear)\n", a);

	return 0;
}
