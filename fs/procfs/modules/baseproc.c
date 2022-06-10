#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/version.h>

/**
 *	/proc/rtoax is a Dir
 *	/pric/rtoax/enable is a trigger
 */

static struct proc_dir_entry *rtoax = NULL;

static bool enable_trigger = false;

static int enable_show(struct seq_file *m, void *ptr)
{
    seq_printf(m, "%s\n", enable_trigger ? "enabled" : "disabled");
    return 0;
}

static int enable_open(struct inode *inode, struct file *file)
{
    return single_open(file, enable_show, inode->i_private);
}

static ssize_t enable_write(struct file *file, const char __user *buf,
		                size_t count, loff_t *ppos)
{
    bool enable;

    if (kstrtobool_from_user(buf, count, &enable))
		return -EINVAL;
    
	if (!!enable == !!enable_trigger) {
        return count;
	}

    if (enable) {
		printk("handle enabled");
	} else {
		printk("handle disabled");
	}

	printk("enable = %d, enable_trigger = %d\n", enable, enable_trigger);
    enable_trigger = enable;
    return count;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 6, 0)
static const struct file_operations rtoax_enable_fops = {
    .open       = enable_open,
    .read       = seq_read,
    .write      = enable_write,
    .llseek     = seq_lseek,
    .release    = single_release,
};
#else
static const struct proc_ops rtoax_enable_fops = {
    .proc_open  = enable_open,
    .proc_read  = seq_read,
    .proc_write = enable_write,
    .proc_lseek = seq_lseek,
    .proc_release   = single_release,
};
#endif

static int __init proctest_init(void)
{
	rtoax = proc_mkdir("rtoax", NULL);
	proc_create("enable", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP, rtoax, &rtoax_enable_fops);
	return 0;
}

static void __exit proctest_exit(void)
{
#if 0
	proc_remove(rtoax_enable);
	proc_remove(rtoax);
#else
	remove_proc_subtree("rtoax", NULL);
#endif
}

module_init(proctest_init);
module_exit(proctest_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("/proc/rtoax/xxx");
