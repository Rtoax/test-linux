#include <stdio.h>
#include <stdint.h>
#include <byteswap.h>

void test_16(void)
{
	int16_t i16 = 1;

	printf("%d = %x\n", i16, i16);
	printf("%d = %x\n", bswap_16(i16), bswap_16(i16));
	printf("%d = %x\n", __bswap_constant_16(i16), __bswap_constant_16(i16));
}

void test_32(void)
{
	int32_t i32 = 1;

	printf("%d = %x\n", i32, i32);
	printf("%d = %x\n", bswap_32(i32), bswap_32(i32));
	printf("%d = %x\n", __bswap_constant_32(i32), __bswap_constant_32(i32));
}

void test_64(void)
{
	int64_t i64 = 1;

	printf("%ld = %lx\n", i64, i64);
	printf("%ld = %lx\n", bswap_64(i64), bswap_64(i64));
	printf("%lld = %llx\n", __bswap_constant_64(i64),
	       __bswap_constant_64(i64));
}

int main(void)
{
	test_16();
	test_32();
	test_64();
	return 0;
}
