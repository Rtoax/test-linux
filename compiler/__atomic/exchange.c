/**
 * type __atomic_exchange_n (type *ptr, type val, int memorder)
 *    tmp = *ptr; *ptr = val; return tmp;
 * void __atomic_exchange (type *ptr, type *val, type *ret, int memorder)
 *    *ret = *ptr; *ptr = *val;
 */
#include <stdio.h>


int main(void)
{
	int a, val, ret;

	a = 10;
	ret = __atomic_exchange_n(&a, 20, __ATOMIC_ACQ_REL);
	printf("a = %d, ret = %d\n", a, ret);

	a = 10;
	val = 20;
	__atomic_exchange(&a, &val, &ret, __ATOMIC_ACQ_REL);
	printf("a = %d, ret = %d\n", a, ret);

	return 0;
}
