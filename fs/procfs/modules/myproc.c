#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#define MAX_LEN 4096

static struct proc_dir_entry *proc_entry;
static char *info;
static int len, temp;

static ssize_t myproc_read(struct file *f, char *user_buf, size_t count,
			 loff_t *off)
{
	int ret;
	/* copy data from kernel space to user space */
	if (count > temp) {
		count = temp;
	}

	temp = temp - count;
	ret = copy_to_user(user_buf, info, count);
	(void)ret;

	if (count == 0)
		temp = len;

	printk(KERN_INFO "procfs_read: read %lu bytes\n", count);
	return count;
}

static ssize_t myproc_write(struct file *f, const char *user_buf, size_t count,
			  loff_t *off)
{
	int ret;
	/* copy data from user space and save it in the my proc entry */
	ret = copy_from_user(info, user_buf, count);
	(void)ret;

	len = count;
	temp = len;

	printk(KERN_INFO "procfs_write: write %lu bytes\n", count);
	return count;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 6, 0)
struct file_operations proc_fops = {
	.read = myproc_read,
	.write = myproc_write,
};
#else
static const struct proc_ops proc_fops = {
	.proc_read = myproc_read,
	.proc_write = myproc_write,
};
#endif

static int init_module1(void)
{
	int ret = 0;

	info = (char *)vmalloc(MAX_LEN);
	memset(info, 0, MAX_LEN);
	proc_entry = proc_create("myproc", 0, NULL, &proc_fops);
	printk(KERN_INFO "myproc created.\n");

	return ret;
}

static void cleanup_module1(void)
{
	remove_proc_entry("myproc", NULL);
	printk(KERN_INFO "test_proc deleted.\n");
	kfree(info);
}

MODULE_LICENSE("GPL");
module_init(init_module1);
module_exit(cleanup_module1);
