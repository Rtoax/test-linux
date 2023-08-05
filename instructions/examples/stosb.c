#include <stdio.h>
#include <sys/types.h>


static inline
void *__memset_generic(void *s, char c, size_t count)
{
	int d0, d1;
	asm volatile("rep\n\t"
			"stosb"
			: "=&c" (d0), "=&D" (d1)
			: "a" (c), "1" (s), "0" (count)
			: "memory");
	return s;
}

int main(void)
{
	char str[1024] = {"1234"};

	printf("str = %s\n", str);
	__memset_generic(str, 0, sizeof(str));
	printf("str = %s\n", str);

	return 0;
}
