/**
 *	File NR_IRQS.c
 *	Time 2021.11.20
 *	Author Rong Tao
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>


static int hello_init(void)
{
	printk(KERN_ALERT "Hi.\n");
    printk(KERN_ALERT "NR_IRQS is %d\n", NR_IRQS);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Bye.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
