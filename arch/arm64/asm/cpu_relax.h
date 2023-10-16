#pragma once

static inline void cpu_relax(void)
{
	asm volatile("yield" ::: "memory");
}
