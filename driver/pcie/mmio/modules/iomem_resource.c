#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/resource.h>
#include <linux/ioport.h>
#include <linux/version.h>

static struct resource res = {
	.name	= "PCI mem Rong Tao",
	.start	= 0x8000000000,
	.end	= 0xffffffffff,
	.flags	= IORESOURCE_MEM,
};

static int kernel_init(void)
{
	printk(KERN_INFO "res init.\n");
	return request_resource(&iomem_resource, &res);
}

static void kernel_exit(void)
{
	printk(KERN_INFO "res exit.\n");
	release_resource(&res);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
