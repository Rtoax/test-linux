#ifndef ____ATomIC_H
#define ____ATomIC_H 1

#include <stdint.h>

#ifndef __x86_64__
# error "Not support Your Arch, just support x86-64"
#endif

/**
 * The atomic counter structure.
 */
typedef struct {
	volatile int64_t cnt;  /**< Internal counter value. */
} atomic64_t;

static inline int
atomic64_cmpset(volatile uint64_t *dst, uint64_t exp, uint64_t src)
{
	uint8_t res;

	asm volatile(
			"lock ; "
			"cmpxchgq %[src], %[dst];"
			"sete %[res];"
			: [res] "=a" (res),     /* output */
			  [dst] "=m" (*dst)
			: [src] "r" (src),      /* input */
			  "a" (exp),
			  "m" (*dst)
			: "memory");            /* no-clobber list */

	return res;
}

static inline uint64_t
atomic64_exchange(volatile uint64_t *dst, uint64_t val)
{
	asm volatile(
			"lock ; "
			"xchgq %0, %1;"
			: "=r" (val), "=m" (*dst)
			: "0" (val),  "m" (*dst)
			: "memory");         /* no-clobber list */
	return val;
}

static inline void
atomic64_init(atomic64_t *v)
{
	atomic64_cmpset((volatile uint64_t *)&v->cnt, v->cnt, 0);
}

static inline int64_t
atomic64_read(atomic64_t *v)
{
	return v->cnt;
}

static inline void
atomic64_set(atomic64_t *v, int64_t new_value)
{
	atomic64_cmpset((volatile uint64_t *)&v->cnt, v->cnt, new_value);
}

static inline void
atomic64_add(atomic64_t *v, int64_t inc)
{
	asm volatile(
			"lock ; "
			"addq %[inc], %[cnt]"
			: [cnt] "=m" (v->cnt)   /* output */
			: [inc] "ir" (inc),     /* input */
			  "m" (v->cnt)
			);
}

static inline void
atomic64_sub(atomic64_t *v, int64_t dec)
{
	asm volatile(
			"lock ; "
			"subq %[dec], %[cnt]"
			: [cnt] "=m" (v->cnt)   /* output */
			: [dec] "ir" (dec),     /* input */
			  "m" (v->cnt)
			);
}

static inline void
atomic64_inc(atomic64_t *v)
{
	asm volatile(
			"lock ; "
			"incq %[cnt]"
			: [cnt] "=m" (v->cnt)   /* output */
			: "m" (v->cnt)          /* input */
			);
}

static inline void
atomic64_dec(atomic64_t *v)
{
	asm volatile(
			"lock ; "
			"decq %[cnt]"
			: [cnt] "=m" (v->cnt)   /* output */
			: "m" (v->cnt)          /* input */
			);
}

static inline int64_t
atomic64_add_return(atomic64_t *v, int64_t inc)
{
	int64_t prev = inc;

	asm volatile(
			"lock ; "
			"xaddq %[prev], %[cnt]"
			: [prev] "+r" (prev),   /* output */
			  [cnt] "=m" (v->cnt)
			: "m" (v->cnt)          /* input */
			);
	return prev + inc;
}

static inline int64_t
atomic64_sub_return(atomic64_t *v, int64_t dec)
{
	return atomic64_add_return(v, -dec);
}

static inline int atomic64_inc_and_test(atomic64_t *v)
{
	uint8_t ret;

	asm volatile(
			"lock ; "
			"incq %[cnt] ; "
			"sete %[ret]"
			: [cnt] "+m" (v->cnt), /* output */
			  [ret] "=qm" (ret)
			);

	return ret != 0;
}

static inline int atomic64_dec_and_test(atomic64_t *v)
{
	uint8_t ret;

	asm volatile(
			"lock ; "
			"decq %[cnt] ; "
			"sete %[ret]"
			: [cnt] "+m" (v->cnt),  /* output */
			  [ret] "=qm" (ret)
			);
	return ret != 0;
}

static inline int atomic64_test_and_set(atomic64_t *v)
{
	return atomic64_cmpset((volatile uint64_t *)&v->cnt, 0, 1);
}

static inline void atomic64_clear(atomic64_t *v)
{
	atomic64_set(v, 0);
}

#endif /*<____ATomIC_H>*/

