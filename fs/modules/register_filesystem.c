/**
 *	File ./register_filesystem.c 
 *	Time 2021.11.09
 *	Author	Rong Tao <rtoax@foxmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/dcache.h> //for d_path()
#include <linux/fs.h>
#include <asm/uaccess.h>

static struct file_system_type myfs_fs_type = {
	.owner = THIS_MODULE,
	.name = "myfs",
	/* TODO */
};

static int __init myfs_init(void)
{
	printk("myfs module is working..\n");
	register_filesystem(&myfs_fs_type);
	return 0;
}

static void __exit myfs_exit(void)
{
	printk("myfs module is leaving..\n");
}

MODULE_LICENSE("GPL");
module_init(myfs_init);
module_exit(myfs_exit);
