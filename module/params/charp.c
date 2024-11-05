#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>


static char *name = "Rong Tao";
module_param(name, charp, 0660);

static int simple_init(void)
{
	printk(KERN_WARNING "name=%s\n", name);
	return -EINVAL;
}

module_init(simple_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
