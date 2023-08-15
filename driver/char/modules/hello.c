#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>


#define HELLO_MAJOR	231
#define DEVICE_NAME	"hellomodule"

static int
hello_open(struct inode *inode, struct file *file)
{
	printk(KERN_EMERG "driver: hello_open\n");
	return 0;
}

static ssize_t
hello_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_EMERG "driver: hello_write\n");
	return 0;
}

static ssize_t
hello_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	printk(KERN_EMERG "driver: hello_read\n");
	return 0;
}

static struct file_operations hello_flops = {
	.owner = THIS_MODULE,
	.open = hello_open,
	.write = hello_write,
	.read = hello_read,
};

static int __init hello_init(void)
{
	int ret = register_chrdev(HELLO_MAJOR, DEVICE_NAME, &hello_flops);
	if (ret < 0) {
		printk(KERN_EMERG DEVICE_NAME " can't register major number.\n");
		return ret;
	}
	printk(KERN_EMERG DEVICE_NAME " initialized.\n");
	return 0;
}

static void __exit hello_exit(void)
{
	unregister_chrdev(HELLO_MAJOR, DEVICE_NAME);
	printk(KERN_EMERG DEVICE_NAME " removed.\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");