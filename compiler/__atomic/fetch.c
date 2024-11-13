/**
 * type __atomic_add_fetch (type *ptr, type val, int memorder)
 * type __atomic_sub_fetch (type *ptr, type val, int memorder)
 * type __atomic_and_fetch (type *ptr, type val, int memorder)
 * type __atomic_xor_fetch (type *ptr, type val, int memorder)
 * type __atomic_or_fetch (type *ptr, type val, int memorder)
 * type __atomic_nand_fetch (type *ptr, type val, int memorder)
 *
 *     { *ptr op= val; return *ptr; }
 *     { *ptr = ~(*ptr & val); return *ptr; } // nand
 *
 *
 * type __atomic_fetch_add (type *ptr, type val, int memorder)
 * type __atomic_fetch_sub (type *ptr, type val, int memorder)
 * type __atomic_fetch_and (type *ptr, type val, int memorder)
 * type __atomic_fetch_xor (type *ptr, type val, int memorder)
 * type __atomic_fetch_or (type *ptr, type val, int memorder)
 * type __atomic_fetch_nand (type *ptr, type val, int memorder)
 *
 *     { tmp = *ptr; *ptr op= val; return tmp; }
 *     { tmp = *ptr; *ptr = ~(*ptr & val); return tmp; } // nand
 */
#include <stdio.h>


int main(void)
{
	/* TODO */
	return 0;
}
