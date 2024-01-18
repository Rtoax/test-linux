#pragma once

#include <stdint.h>

#ifndef ASM_CAS_X86_64
#define ASM_CAS_X86_64(ptr, val_old, val_new) ({ \
	char ret; \
	__asm__ __volatile__("lock; "\
		"cmpxchgl %2,%0; setz %1"\
		: "+m"(*ptr), "=q"(ret)\
		: "r"(val_new),"a"(val_old)\
		: "memory"); \
	ret;})
#endif

#define _val_compare_and_swap(ptr, oldval, newold) __sync_val_compare_and_swap(ptr, oldval, newold)
#define _bool_compare_and_swap(loc, oldval, newval) __sync_bool_compare_and_swap((void **)loc, oldval, newval)
#define CAS(loc, old, new) _bool_compare_and_swap(loc, old, new)

#define _add_and_fetch(ptr, v)  __sync_add_and_fetch(ptr, v)
#define _sub_and_fetch(ptr, v)  __sync_sub_and_fetch(ptr, v)
#define _or_and_fetch(ptr, v)  __sync_or_and_fetch(ptr, v)
#define _and_and_fetch(ptr, v)  __sync_and_and_fetch(ptr, v)
#define _xor_and_fetch(ptr, v)  __sync_xor_and_fetch(ptr, v)
#define _nand_and_fetch(ptr, v)  __sync_nand_and_fetch(ptr, v)

#define _fetch_and_add(ptr, v)  __sync_fetch_and_add(ptr, v)
#define _fetch_and_sub(ptr, v)  __sync_fetch_and_sub(ptr, v)
#define _fetch_and_or(ptr, v)  __sync_fetch_and_or(ptr, v)
#define _fetch_and_and(ptr, v)  __sync_fetch_and_and(ptr, v)
#define _fetch_and_xor(ptr, v)  __sync_fetch_and_xor(ptr, v)
#define _fetch_and_nand(ptr, v)  __sync_fetch_and_nand(ptr, v)


#if defined(__x86_64__)
static uint64_t __cas(uint64_t* addr, uint64_t nval, uint64_t cmp)
{
	uint64_t old;
	__asm__ __volatile__(
		"lock cmpxchg8b %0\n\t"
		: "=a" (old), "+m" (*addr)
		: "d" ((uint32_t)(cmp >> 32)), "a" ((uint32_t)(cmp & 0xffffffff)),
		  "c" ((uint32_t)(nval >> 32)), "b" ((uint32_t)(nval & 0xffffffff))
		: "cc"
	);
}
#endif

