volatile int lock = 0;

void *worker(void *arg)
{
	while (__sync_lock_test_and_set(&lock, 1));
	/* critical section */
	__sync_lock_release(&lock);
}

