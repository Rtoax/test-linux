#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

struct display_arg {
	struct file_system_type *fstype;
};

static void display_sb(struct super_block *sb, void *arg)
{
	struct display_arg *darg = arg;
	pr_info("Superblock: fsname=%s, dev=%s, type=%s, flags=0x%lx\n",
		darg->fstype->name, sb->s_id, sb->s_type->name, sb->s_flags);
}

static int kernel_init(void)
{
	int i;
	char *fs[] = { "efivarfs", "ext4", "proc", "tmpfs", "xfs" };

	printk(KERN_INFO "Display super_block.\n");

	for (i = 0; i < ARRAY_SIZE(fs); i++) {
		struct file_system_type *fstype = get_fs_type(fs[i]);
		struct display_arg arg = {
			.fstype = fstype,
		};

		/**
		 * void iterate_supers_type(struct file_system_type *type,
		 *          void (*f)(struct super_block *, void *), void *arg);
		 */
		iterate_supers_type(fstype, display_sb, &arg);
	}
	/* exit directly */
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
