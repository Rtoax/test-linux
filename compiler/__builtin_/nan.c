#include <stdio.h>
#include <stdint.h>

#define print_nan(str) do { \
	double d = __builtin_nan(str); \
	printf("Built-in nan("str") %lf : 0x%016lx\n", d, *(uint64_t *)&d); \
} while (0)

int main(int argc, char *argv[])
{
	print_nan("");
	print_nan("123");
	print_nan("0xabc");
	print_nan("65535");
	return 0;
}
