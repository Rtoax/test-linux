#pragma once

static int currentel(void)
{
#if defined(__aarch64__)
	register uint64_t x0 __asm__ ("x0");
	/* or just use read_sysreg(CurrentEL) to get x0 */
	__asm__ ("mrs x0, CurrentEL;" : : : "%x0");
	return x0 >> 2;
#elif defined(__arm__)
	register uint32_t r0 __asm__ ("r0");
	__asm__ ("mrs r0, CPSR" : : : "%r0");
	return r0 & 0x1F;
#endif
}
