#include <linux/module.h>
#include <linux/delay.h>
#include <linux/rcupdate.h>

static int rcu_cpu_stall_timeout = CONFIG_RCU_CPU_STALL_TIMEOUT + 1;

static int __init test_init(void)
{
	rcu_read_lock();
	/* busy delay 20s */
	mdelay(rcu_cpu_stall_timeout);
	rcu_read_unlock();
	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
