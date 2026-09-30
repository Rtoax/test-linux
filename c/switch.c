#include <stdio.h>

void test(int c)
{
	switch (c) {
#define C(v)                        \
	case v:                     \
		printf("%s\n", #v); \
		break
		C(1);
		C(2);
		C(3 ... 4);
#undef C
	}
}

int main(int argc, char *argv[])
{
	test(1);
	test(3);
	return 0;
}
