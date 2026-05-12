#include <linux/module.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/path.h>

static int __init mymod_init(void)
{
	int err;
	struct path path;
	struct super_block *sb = NULL;

	err = kern_path("/etc/os-release", LOOKUP_FOLLOW, &path);
	if (err) {
		pr_err("kern_path failed: %d\n", err);
		return err;
	}

	sb = path.dentry->d_sb;
	atomic_inc(&sb->s_active);

	path_put(&path);
	drop_super(sb);
	return -EINVAL;
}

module_init(mymod_init);
MODULE_LICENSE("GPL");
