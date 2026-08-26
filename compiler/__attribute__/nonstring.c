/**
 * This attribute applies to variables or members of a struct, union, or class
 * that have type array of char, signed char, or unsigned char, or pointer to
 * such a type.
 *
 * The nonstring attribute specifies that an object or member of such a type is
 * intended to store character arrays that do not necessarily contain a
 * terminating NUL. This is useful in detecting uses of such arrays or pointers
 * with functions that expect NUL-terminated strings, and to avoid warnings
 * when such an array or pointer is used as an argument to a bounded string
 * manipulation function such as strncpy. For example, without the attribute,
 * GCC issues a warning for the strncpy call below because it may truncate the
 * copy without appending the terminating NUL character. Using the attribute
 * makes it possible to suppress the warning. However, when the array is
 * declared with the attribute the call to strlen is diagnosed because when
 * the array doesn’t contain a NUL-terminated string the call is undefined.
 * To copy, compare, or search non-string character arrays use the memcpy,
 * memcmp, memchr, and other functions that operate on arrays of bytes. In
 * addition, calling strnlen and strndup with such arrays is safe provided a
 * suitable bound is specified, and not diagnosed.
 *
 * Refs:
 * - gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-nonstring
 */

#include <stdio.h>
#include <string.h>

#define __nonstring __attribute__((nonstring))

struct data {
	char name[8] __nonstring;
};

int main(void)
{
	struct data data;
	strncpy(data.name, "1234567890", sizeof(data.name));

#ifdef ERROR
	/**
	 * error: ‘__builtin_puts’ argument 1 declared attribute ‘nonstring’
	 */
	printf("%s\n", data.name);
#endif
	return 0;
}
