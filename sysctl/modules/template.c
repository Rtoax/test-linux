/**
 *	File 
 *	Time 2021.11.12
 *	Author	Rong Tao <rtoax@foxmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysctl.h>


static int __init my_init(void)
{
	printk("my module is working..\n");
	return 0;
}

static void __exit my_exit(void)
{
	printk("my module is leaving..\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
