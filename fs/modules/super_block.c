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
	printk(KERN_INFO "Display super_block.\n");
#if 0 /* super_blocks is static variable */
	struct super_block *sb;
	spin_lock(&sb_lock);
	list_for_each_entry(sb, &super_blocks, s_list)
		display_sb(sb, NULL);
	spin_unlock(&sb_lock);
#elif 0 /* not exported */
	iterate_supers(display_sb, NULL);
#elif 1
	int i;
	char *fs[] = { "xfs", "ext4", "proc" };
	for (i = 0; i < ARRAY_SIZE(fs); i++) {
		struct file_system_type *fstype = get_fs_type(fs[i]);
		struct display_arg arg = {
			.fstype = fstype,
		};
		iterate_supers_type(fstype, display_sb, &arg);
	}
#endif
	/* exit directly */
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
