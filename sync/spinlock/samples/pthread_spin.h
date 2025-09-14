#pragma once

#include <pthread.h>

typedef pthread_spinlock_t spinlock_t;

#define SPINLOCK() Do not use

static inline void spinlock_init(spinlock_t *lock)
{
	pthread_spin_init(lock, PTHREAD_PROCESS_SHARED);
}

static inline void spinlock_lock(spinlock_t *lock)
{
	pthread_spin_lock(lock);
}

static inline void spinlock_unlock(spinlock_t *lock)
{
	pthread_spin_unlock(lock);
}

static inline void spinlock_destroy(spinlock_t *lock)
{
	pthread_spin_destroy(lock);
}
