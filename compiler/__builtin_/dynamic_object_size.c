/**
 * size_t __builtin_dynamic_object_size(const void *ptr, int type);
 *
 * Need _FORTIFY_SOURCE=1/2/3
 *
 * Runtime.
 * See also __builtin_object_size(), __attribute__((__counted_by__(n))).
 *
 * Refs:
 * - https://people.kernel.org/gustavoars/how-to-use-the-new-counted_by-attribute-in-c-and-linux
 */
#include <stdio.h>
#include <malloc.h>
#include "__counted_by__.h"

struct flex_struct {
	size_t count;
	int flex_array[] __counted_by(count);
};

int main(void)
{
	int count;
	struct flex_struct *flex;

	count = 4;
	flex = malloc(sizeof(struct flex_struct) + sizeof(int) * count);

	flex->count = count;
	flex->flex_array[0] = 1;
	flex->flex_array[1] = 2;

	printf("%ld\n", __builtin_dynamic_object_size(flex->flex_array, 0));
	printf("%ld\n", __builtin_dynamic_object_size(flex->flex_array, 1));

	free(flex);
	return 0;
}
