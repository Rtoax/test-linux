#include <linux/module.h>
#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/pagemap.h>
#include <linux/mount.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/cred.h> // current_fsuid/current_fsgid
#include <linux/kfifo.h> // misc
#include <linux/version.h>

#define MYFS_MAGIC 0X64668735
#define MYFS "myfs"

/* TODO */
#ifndef VMACACHE_SIZE
#define VMACACHE_BITS 2
#define VMACACHE_SIZE (1U << VMACACHE_BITS)
#endif

static struct vfsmount * myfs_mount;
static int myfs_mount_count;

DEFINE_KFIFO(mydemo_fifo, char, 64);

int g_val;

static struct inode * myfs_get_inode(struct super_block * sb, int mode, dev_t dev)
{
	struct inode *inode = new_inode(sb);

	if (inode) {
		inode->i_mode = mode;
		inode->i_uid = current_fsuid();
		inode->i_gid = current_fsgid();
		inode->i_size = VMACACHE_SIZE;
		inode->i_blocks = 0;
		struct timespec64 curtime = current_time(inode);
/**
 * kernel commit 3aa63a569c64 ("fs: switch timespec64 fields in inode to discrete integers")
 * v6.10-rc1-2-g3aa63a569c64
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 10, 0)
		inode->i_atime_sec = inode->i_mtime_sec = curtime.tv_sec;
		inode->i_atime_nsec = inode->i_mtime_nsec = curtime.tv_nsec;
/**
 * kernel commit 12cd44023651 ("fs: rename inode i_atime and i_mtime fields")
 * v6.6-rc5-86-g12cd44023651
 */
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(6, 6, 0)
		inode->__i_atime = inode->__i_mtime = curtime;
#else
		inode->i_atime = inode->i_mtime = curtime;
#endif
		inode_set_ctime_to_ts(inode, curtime);

		switch (mode & S_IFMT) {
			case S_IFREG:
				printk("creat a file\n");
				break;
			case S_IFDIR:
				printk("creat a content\n");
				inode->i_op = &simple_dir_inode_operations;
				inode->i_fop = &simple_dir_operations;
				inc_nlink(inode);
				break;
			default:
				init_special_inode(inode,mode,dev);
				break;
		}
	}
	return inode;
}

static int myfs_mknod(struct inode *dir, struct dentry *dentry, int mode,
		      dev_t dev)
{
	struct inode * inode;
	int error = -EPERM;

	if (dentry -> d_inode)
		return -EPERM;

	inode = myfs_get_inode(dir->i_sb, mode, dev);
	if (inode) {
		d_instantiate(dentry,inode);
		dget(dentry);
		error = 0;
	}
	return error;
}

static int myfs_mkdir(struct inode * dir, struct dentry * dentry, int mode)
{
	int res;

	res = myfs_mknod(dir, dentry, mode|S_IFDIR, 0);
	if (!res) {
		inc_nlink(dir);
	}
	return res;
}

static int myfs_creat(struct inode * dir, struct dentry * dentry, int mode)
{
	return myfs_mknod(dir, dentry, mode|S_IFREG, 0);
}

static int myfs_fill_super(struct super_block *sb, void *data, int silent)
{
	static struct tree_descr debug_files[] = {{""}};

	return simple_fill_super(sb, MYFS_MAGIC, debug_files);
}

static struct dentry *myfs_get_sb(struct file_system_type *fs_type, int flags,
		const char *dev_name, void *data)
{
	return mount_single(fs_type, flags, data, myfs_fill_super);
}

static int myfs_file_open(struct inode *inode, struct file *file)
{
	printk("已打开文件");
	return 0;
}

static ssize_t myfs_file_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int actual_readed;
	int ret;

	ret = kfifo_to_user(&mydemo_fifo,buf, count, &actual_readed);
	if (ret)
		return -EIO;

	printk("%s,actual_readed=%d,pos=%lld\n",__func__,actual_readed,*ppos);

	return actual_readed;
}

static ssize_t myfs_file_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	unsigned int actual_write;
	int ret;

	ret = kfifo_from_user(&mydemo_fifo, buf, count, &actual_write);
	if (ret)
		return -EIO;

	printk("%s: actual_write=%d,ppos=%lld\n",__func__,actual_write,*ppos);
	return actual_write;
}

static struct file_system_type my_fs_type = {
	.owner 		= THIS_MODULE,
	.name 		= MYFS,
	.mount 		= myfs_get_sb,
	.kill_sb 	= kill_litter_super
};

static struct file_operations myfs_file_operations = {
	.open = myfs_file_open,
	.read = myfs_file_read,
	.write = myfs_file_write,
};

static int myfs_creat_by_name(const char *name, mode_t mode,
			      struct dentry *parent, struct dentry **dentry)
{
	int error = 0;

	if (!parent) {
		if (myfs_mount && myfs_mount -> mnt_sb) {
			parent = myfs_mount->mnt_sb->s_root;
		}
	}

	if (!parent) {
		printk("can't find a parent");
		return -EFAULT;
	}

	*dentry = NULL;

	inode_lock(d_inode(parent));
/**
 * linux commit fa6fe07d1536 ("VFS: rename lookup_one_len family to lookup_noperm and remove permission check")
 * v6.15-rc1-4-gfa6fe07d1536
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 15, 0)
	*dentry = lookup_noperm(&QSTR(name), parent);
#else
	*dentry = lookup_one_len(name, parent, strlen(name));
#endif
	if (!IS_ERR(*dentry)) {
		if ((mode & S_IFMT) == S_IFDIR) {
			error = myfs_mkdir(parent->d_inode, *dentry, mode);
		} else {
			error = myfs_creat(parent->d_inode, *dentry, mode);
		}
	}
	if (IS_ERR(*dentry)) {
		error = PTR_ERR(*dentry);
	}
	inode_unlock(d_inode(parent));

	return error;
}

static struct dentry *myfs_creat_file(const char *name, mode_t mode,
				      struct dentry *parent, void *data,
				      struct file_operations *fops)
{
	struct dentry * dentry = NULL;
	int error;

	printk("myfs:creating file '%s'\n",name);

	error = myfs_creat_by_name(name, mode, parent, &dentry);

	if (error) {
		dentry = NULL;
		goto exit;
	}

	if (dentry->d_inode) {
		if(data)
			dentry->d_inode->i_private = data;
		if(fops)
			dentry->d_inode->i_fop = fops;
	}

exit:
	return dentry;
}

static struct dentry *myfs_creat_dir(const char *name, struct dentry *parent)
{
	return myfs_creat_file(name, S_IFDIR|S_IRWXU|S_IRUGO, parent, NULL, NULL);
}

static int __init myfs_init(void)
{
	int retval;
	struct dentry * pslot;

	retval = register_filesystem(&my_fs_type);

	if (!retval) {
		/* create super_block dentry's inode */
		myfs_mount = kern_mount(&my_fs_type);
		if (IS_ERR(myfs_mount)) {
			printk("--ERROR:aufs could not mount!--\n");
			unregister_filesystem(&my_fs_type);
			return retval;
		}
	}

	pslot = myfs_creat_dir("First", NULL);
	myfs_creat_file("one", S_IFREG|S_IRUGO|S_IWUSR, pslot, NULL, &myfs_file_operations);
	myfs_creat_file("two", S_IFREG|S_IRUGO|S_IWUSR, pslot, NULL, &myfs_file_operations);

	pslot = myfs_creat_dir("Second", NULL);
	myfs_creat_file("one", S_IFREG|S_IRUGO|S_IWUSR, pslot, NULL, &myfs_file_operations);
	myfs_creat_file("two", S_IFREG|S_IRUGO|S_IWUSR, pslot, NULL, &myfs_file_operations);

	return retval;
}

static void __exit myfs_exit(void)
{
	simple_release_fs(&myfs_mount, &myfs_mount_count);
	unregister_filesystem(&my_fs_type);
}

module_init(myfs_init);
module_exit(myfs_exit);
MODULE_LICENSE("GPL");
