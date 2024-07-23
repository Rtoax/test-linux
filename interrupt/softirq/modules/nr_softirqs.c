#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "init: Hello, world\n");
	printk(KERN_ALERT "init: NR_SOFTIRQS is %d\n", NR_SOFTIRQS);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "init: Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
