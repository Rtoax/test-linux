#pragma once

#include <emmintrin.h>

typedef struct {
	/* 1:locked, 0:unlocked */
	volatile int locked;
} spinlock_t;

#define SPINLOCK() {0}

static inline void spinlock_init(spinlock_t *lock)
{
	lock->locked = 0;
}

static inline void ____pause(void)
{
	_mm_pause();
}

static inline void spinlock_lock(spinlock_t *lock)
{
	while ( __sync_lock_test_and_set(&lock->locked, 1) == 1)
		while (lock->locked == 1)
			____pause();
}

static inline void spinlock_unlock(spinlock_t *lock)
{
	__sync_lock_release(&lock->locked);
}

static inline void spinlock_destroy(spinlock_t *lock)
{
	return;
}
