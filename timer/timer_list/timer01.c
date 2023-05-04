/**
 *	File timer.c
 *	Time 2021.11.03
 *	Author	Rong Tao <cestc.cn>
 *	
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/kernel.h>

static void
time_handler(struct timer_list* data);

DEFINE_TIMER(stimer, time_handler);

static void 
time_handler(struct timer_list* data)
{
	mod_timer(data, jiffies + HZ);
	printk("current jiffies is %ld\n", jiffies);
}

static int __init timer_init(void)
{
	printk("My module worked!\n");
#if 1
	stimer.expires = jiffies + HZ;
	stimer.function = time_handler;
#endif
	add_timer(&stimer);
	return 0;
}

static void
__exit timer_exit(void)
{
	printk("Unloading my module.\n");
	del_timer(&stimer);
	return;
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");

