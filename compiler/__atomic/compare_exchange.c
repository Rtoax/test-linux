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
 * bool __atomic_compare_exchange (type *ptr, type *expected, type *desired,
 *                                 bool weak, int success_memorder,
 *                                 int failure_memorder)
 *   - only desired value is a pointer
 */
#include <stdio.h>


int main(void)
{
	/* TODO */
	return 0;
}
