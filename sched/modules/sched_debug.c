#include <linux/kernel.h>
#include <linux/module.h>
#include <uapi/linux/sched.h>
#include <linux/init_task.h>
#include <linux/init.h>
#include <linux/fdtable.h>
#include <linux/fs_struct.h>
#include <linux/mm_types.h>
#include <linux/version.h>


static int __init sched_debug(void)
{
	/**
	 * TODO: /proc/sched_debug
	 */
	return 0;
}

static void __exit debug_exit(void)
{
	printk("exiting...\n");
}

module_init(sched_debug);
module_exit(debug_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
