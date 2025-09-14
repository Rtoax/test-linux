/**
 * https://www.kernel.org/doc/html/latest/RCU/whatisRCU.html
 */
#include <linux/kernel.h>
#include <linux/rwlock.h>


static DEFINE_RWLOCK(rcu_gp_mutex);

void rcu_read_lock(void)
{
	read_lock(&rcu_gp_mutex);
}

void rcu_read_unlock(void)
{
	read_unlock(&rcu_gp_mutex);
}

void synchronize_rcu(void)
{
	write_lock(&rcu_gp_mutex);
	smp_mb__after_spinlock();
	write_unlock(&rcu_gp_mutex);
}

#define rcu_assign_pointer(p, v) \
({ \
	smp_store_release(&(p), (v)); \
})

#define rcu_dereference(p) \
({ \
	typeof(p) _________p1 = READ_ONCE(p); \
	(_________p1); \
})
