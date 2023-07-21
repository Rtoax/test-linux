#include <stdio.h>
#include <stdint.h>


static inline uint32_t __arch_swab32(uint32_t val)
{
	__asm__("bswapl %0" : "=r" (val) : "0" (val));
	return val;
}

static inline uint64_t __arch_swab64(uint64_t val)
{
#ifdef __i386__
	union {
		struct {
			__u32 a;
			__u32 b;
		} s;
		uint64_t u;
	} v;
	v.u = val;
	__asm__("bswapl %0 ; bswapl %1 ; xchgl %0,%1"
			: "=r" (v.s.a), "=r" (v.s.b)
			: "0" (v.s.a), "1" (v.s.b));
	return v.u;
#else /* __i386__ */
	__asm__("bswapq %0" : "=r" (val) : "0" (val));
	return val;
#endif
}

int main(void)
{
	uint32_t u32 = 0x12345678;
	uint32_t u32swab = __arch_swab32(u32);
	uint64_t u64 = 0x1234567890abcdef;
	uint64_t u64swab = __arch_swab64(u64);

	printf("swab32(%x) = %x\n", u32, u32swab);
	printf("swab64(%lx) = %lx\n", u64, u64swab);

	return 0;
}
