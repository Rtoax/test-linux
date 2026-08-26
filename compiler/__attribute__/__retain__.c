/**
 * This attribute applies to functions and variables.
 *
 * For ELF targets that support the GNU or FreeBSD OSABIs, this attribute
 * protects the function or variable it applies to from linker garbage
 * collection. To support this behavior, functions and variables that have
 * not been placed in specific sections (e.g. by the section attribute, or
 * the -ffunction-sections or -fdata-sections options) are placed in new,
 * unique sections.
 *
 * This additional functionality requires Binutils version 2.36 or later.
 *
 * Refs:
 * - gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-retain
 * - clang: https://clang.llvm.org/docs/AttributeReference.html#retain
 */
#include <stdio.h>

#if __has_attribute(__retain__)
#define __retain __attribute__((__retain__))
#else
#define __retain
#endif

__retain int foo_i_retain;
int foo_i;

__retain void foo_retain(void)
{
}

void foo(void)
{
}

int main(void)
{
	foo_retain();
	foo();

	return 0;
}
