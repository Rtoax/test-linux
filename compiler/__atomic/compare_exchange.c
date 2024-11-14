/**
 * bool __atomic_compare_exchange_n (type *ptr, type *expected, type desired,
 *                                   bool weak, int success_memorder,
 *                                   int failure_memorder)
 *   if (*ptr == *expected) {
 *     // read-modify-write operation
 *     // memorder: success_memorder
 *     *ptr = desired;
 *     return true;
 *   } else {
 *     // operation is a read
 *     // memorder: failure_memorder
 *     *expected = *ptr;
 *     return false;
 *   }
 *
 *   failure_memorder cannot be __ATOMIC_RELEASE nor __ATOMIC_ACQ_REL
 *
 * bool __atomic_compare_exchange (type *ptr, type *expected, type *desired,
 *                                 bool weak, int success_memorder,
 *                                 int failure_memorder)
 *   - only desired value is a pointer
 */
#include <stdio.h>
#include <stdbool.h>


int main(void)
{
	int val, expected, desired;
	bool weak, ret;

	val = 1;
	expected = 1;
	desired = 2;
	weak = true;
	ret = __atomic_compare_exchange_n(&val, &expected, desired, weak,
				  __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	printf("val = %d, expected = %d, ret = %d\n", val, expected, ret);

	val = 1;
	expected = 2;
	desired = 2;
	weak = true;
	ret = __atomic_compare_exchange_n(&val, &expected, desired, weak,
				  __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	printf("val = %d, expected = %d, ret = %d\n", val, expected, ret);

	val = 1;
	expected = 2;
	desired = 2;
	weak = true;
	ret = __atomic_compare_exchange(&val, &expected, &desired, weak,
				  __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	printf("val = %d, expected = %d, ret = %d\n", val, expected, ret);

	return 0;
}
