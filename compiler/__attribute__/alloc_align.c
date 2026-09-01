/**
 * alloc_align (position)
 *
 * The alloc_align attribute may be applied to a function that returns a
 * pointer and takes at least one argument of an integer or enumerated type.
 * 
 * It indicates that the returned pointer is aligned on a boundary given by the
 * function argument at position. Meaningful alignments are powers of 2 greater
 * than one. GCC uses this information to improve pointer alignment analysis.
 * 
 * The function parameter denoting the allocated alignment is specified by one
 * constant integer argument whose number is the argument of the attribute.
 * Argument numbering starts at one.
 *
 * Refs:
 * - https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-alloc_005falign
 */
#include <stdio.h>

void *my_memalign(size_t, size_t) __attribute__((alloc_align(1)));

int main(void)
{
	return 0;
}
