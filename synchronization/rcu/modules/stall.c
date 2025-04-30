#include <linux/module.h>
#include <linux/printk.h>
#include <linux/delay.h>
#include <linux/rcupdate.h>

static int stall_type = 1;

module_param(stall_type, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(stall_type, "RCU stall type");

static int rcu_cpu_stall_timeout = CONFIG_RCU_CPU_STALL_TIMEOUT + 1;

static void stall_1(void)
{
	printk(KERN_INFO "rcu_cpu_stall_timeout %d s\n", rcu_cpu_stall_timeout);
	rcu_read_lock();
	/* busy delay */
	mdelay(rcu_cpu_stall_timeout * 1000);
	rcu_read_unlock();
}

static int __init test_init(void)
{
	switch (stall_type) {
	case 1:
		stall_1();
		break;
	default:
		return -EINVAL;
	}

	return -EPERM;
}

module_init(test_init);
MODULE_LICENSE("GPL");
