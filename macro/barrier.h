#pragma once

#define mb()	asm volatile("mfence":::"memory")
#define synchronize()	__sync_synchronize() /* = mb() */
