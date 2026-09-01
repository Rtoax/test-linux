/**
 * Refs:
 * - https://people.kernel.org/gustavoars/how-to-use-the-new-counted_by-attribute-in-c-and-linux
 */
#include <stdio.h>
#include "compiler.h"

struct foo {
	int i;
};

struct bounded_flex_struct {
	size_t count;
	struct foo flex_array[] __counted_by(count);
};

int main(void)
{
	printf("size of %ld\n", sizeof(struct bounded_flex_struct));
	return 0;
}
