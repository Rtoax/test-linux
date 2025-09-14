#pragma once

typedef struct {
} spinlock_t;

#define SPINLOCK() {}

static inline void spinlock_init(spinlock_t *lock)
{}

static inline void spinlock_lock(spinlock_t *lock)
{}

static inline void spinlock_unlock(spinlock_t *lock)
{}

static inline void spinlock_destroy(spinlock_t *lock)
{}
