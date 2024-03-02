/**
 *	File	clocksource_resigter_hz.c
 *	Time	2022.01.10
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/clocksource.h>

#include <asm/pvclock.h>
#include <asm/kvmclock.h>

struct task_struct *task;
char *THREAD_MESSAGE = "Hello from MyThread!";

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
    clocksource_register_hz(&kvm_clock, NSEC_PER_SEC/2);
    return 0;
}

static void kernel_exit(void)
{
    printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
