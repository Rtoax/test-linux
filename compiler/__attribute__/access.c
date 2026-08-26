/**
 * access (access-mode, ref-index)
 * access (access-mode, ref-index, size-index)
 *
 * This attribute applies to functions.
 *
 * The access attribute enables the detection of invalid or unsafe accesses by
 * functions or their callers, as well as write-only accesses to objects that
 * are never read from. Such accesses may be diagnosed by warnings such as
 * -Wstringop-overflow, -Wuninitialized, -Wunused, and others.
 *
 * Refs:
 * - gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-access
 */
#include <stdio.h>

__attribute__((access(write_only, 1), access(read_only, 2)))
void foo1(char *s1, const char *s2)
{
	s1[0] = 'a';
#ifdef ERROR
	s2[0] = 'a';
#endif
}

__attribute__((access(write_only, 1), access(read_only, 2)))
void foo2(char *s1, char *s2)
{
	s1[0] = 'a';
	s2[0] = s1[0];
}

int main(void)
{
	char s1[8] = { "Hello" };
	char s2[8] = { "World" };

	foo1(s1, s2);
	foo2(s1, s2);

	return 0;
}
