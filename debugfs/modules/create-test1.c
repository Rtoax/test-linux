/**
 *	File create.c
 *	Time 2021.11.03
 *	Author Rong Tao
 */
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/init.h>
#include <linux/printk.h>

struct dentry *debugfs_root;

static int debug_seq_show(struct seq_file *s, void *v)
{
	seq_printf(s, "debug seq show.\n");
	// more printf
	return 0;
}

static int debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, debug_seq_show, NULL);
}

static const struct file_operations debugfs_ops = {
	owner: THIS_MODULE,
	open: debug_open,
	read: seq_read,
	llseek: seq_lseek,
	// not seq_release, because we use single_open
	release: single_release,
};

static int __init debugfs_init(void)
{
	pr_warn("Init debugfs dir.\n");
	debugfs_root = debugfs_create_dir("rongtao", NULL);
	if(!debugfs_root) {
		return -ENOMEM;
	}
	if(!debugfs_create_file("test1", 0444, debugfs_root, NULL, &debugfs_ops)) {
		goto fail;
	}
	return 0;
fail:
	debugfs_remove_recursive(debugfs_root);
	return -ENOMEM;
}

static void __exit debugfs_exit(void)
{
	pr_warn("Bye.\n");
	debugfs_remove_recursive(debugfs_root);
}

module_init(debugfs_init);
module_exit(debugfs_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
