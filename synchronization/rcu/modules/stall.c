/**
 * What Causes RCU CPU Stall Warnings?
 *
 * - A CPU looping in an RCU read-side critical section.
 * - A CPU looping with interrupts disabled.
 * - A CPU looping with preemption disabled.
 * - A CPU looping with bottom halves disabled.
 *
 * Refs:
 * - https://www.kernel.org/doc/html/latest/RCU/stallwarn.html
 */
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/delay.h>
#include <linux/rcupdate.h>

static int stall_type = 1;
static int sleep = 0;

module_param(stall_type, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(stall_type, "RCU stall type");
module_param(sleep, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(sleep, "RCU stall type");

static int rcu_cpu_stall_timeout = CONFIG_RCU_CPU_STALL_TIMEOUT + 1;

static inline void timeout(void)
{
	if (sleep)
		msleep(rcu_cpu_stall_timeout * 1000);
	else
		/* busy delay */
		mdelay(rcu_cpu_stall_timeout * 1000);
}

/**
 * commit 2f53652af601 ("rcu/modules: stall.c: test on 6.12.0-77.el10.x86_64")
 * commit 7474b72b5caf ("rcu/modules: stall.c: could use msleep instead of mdelay")
 */
static void stall_1_looping_in_read_side(void)
{
	rcu_read_lock();
	timeout();
	rcu_read_unlock();
}

static void stall_2_looping_with_irq_disabled(void)
{
	if (sleep)
		printk(KERN_ERR "Sleeping with interrupts disabled will not cause RCU stall.\n");
	/* or use spin_lock_irq() */
	local_irq_disable();
	timeout();
	local_irq_enable();
}

/**
 * commit 80af9853c093 ("rcu/modules: stall.c: looping with preemption disabled")
 */
static void stall_3_looping_with_preemption_disabled(void)
{
	if (sleep)
		printk(KERN_ERR "Sleeping with preemption disabled will not cause RCU stall.\n");
	preempt_disable();
	timeout();
	preempt_enable();
}

/**
 * commit 2d43a8a43327 ("rcu/modules: stall.c: looping with bottom halves disabled")
 */
static void stall_4_looping_with_bh_disabled(void)
{
	if (sleep)
		printk(KERN_ERR "Sleeping with bottom halves disabled will not cause RCU stall.\n");
	/* or use spin_lock_bh() */
	local_bh_disable();
	timeout();
	local_bh_enable();
}

static int __init test_init(void)
{
	printk(KERN_INFO "rcu_cpu_stall_timeout %d s\n", rcu_cpu_stall_timeout);
	printk(KERN_INFO "Test RCU stall type %d with sleep %d\n", stall_type,
		sleep);

	switch (stall_type) {
	case 1:
		stall_1_looping_in_read_side();
		break;
	case 2:
		stall_2_looping_with_irq_disabled();
		break;
	case 3:
		stall_3_looping_with_preemption_disabled();
		break;
	case 4:
		stall_4_looping_with_bh_disabled();
		break;
	default:
		return -EINVAL;
	}

	return -EPERM;
}

module_init(test_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
