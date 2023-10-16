/**
 *	File	rwlock_init.c
 *	Time	2021.11.11
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/rwlock.h>

static rwlock_t my_rwlock;

DEFINE_RWLOCK(my_rwlock2);

static int kernel_init(void)
{
	printk(KERN_INFO "Init.\n");
	rwlock_init(&my_rwlock);	
	return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "Exit\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
