/**
 * bool __sync_bool_compare_and_swap (type *ptr, type oldval type newval, ...)
 * type __sync_val_compare_and_swap (type *ptr, type oldval type newval, ...)
 *
 * - If the current value of *ptr is oldval, then write newval into *ptr;
 * - The 'bool' version returns true if the comparison is successful and newval was written;
 * - The 'val' version returns the contents of *ptr before the operation;
 *
 *   if (*ptr == old) {
 *     *ptr = new;
 *     return true;
 *   }
 *   return false;
 *
 *   if (*ptr == old) {
 *     *ptr = new;
 *     return old;
 *   }
 *   return *ptr;
 */
#include <stdio.h>
#include <stdbool.h>

#ifndef cmpxchg
#define cmpxchg(ptr, o, n)		    \
({									\
	__typeof__(*(ptr)) __o = (o);					\
	__typeof__(*(ptr)) __n = (n);					\
	(__typeof__(*(ptr))) __sync_val_compare_and_swap((ptr),__o,__n);\
})
#endif
#define cmpxchg_bool(ptr, o, n)		    \
({									\
	__typeof__(*(ptr)) __o = (o);					\
	__typeof__(*(ptr)) __n = (n);					\
	__sync_bool_compare_and_swap((ptr), __o, __n);			\
})

int main(void)
{
	int a, ret;

	a = 10;
	ret = cmpxchg(&a, 10, 20);
	printf("a = %d, ret = %d\n", a, ret);

	ret = cmpxchg(&a, 10, 20);
	printf("a = %d, ret = %d\n", a, ret);

	a = 10;
	ret = cmpxchg_bool(&a, 10, 20);
	printf("a = %d, ret = %d\n", a, ret);

	ret = cmpxchg_bool(&a, 10, 20);
	printf("a = %d, ret = %d\n", a, ret);

	return 0;
}
