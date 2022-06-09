/**
 *	File	KERNEL_VERSION.c
 *	Time	2021.11.20
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/utsname.h>
#include <linux/version.h>

static int kernel_init(void)
{
    printk(KERN_INFO "my init.\n");
#define	S(v) \
	printk(KERN_INFO "init_uts_ns.%s = %s\n", #v, init_uts_ns.v)
#define	I(v) \
	printk(KERN_INFO "init_uts_ns.%s = %d\n", #v, init_uts_ns.v)

	/**
	 *	Don't have kref since >=5.11
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 11, 0)
	printk("init_nts_ns.kref = %d\n", kref_read(&init_uts_ns.kref));
#endif
	S(name.sysname);
	S(name.nodename);
	S(name.release);
	S(name.version);
	S(name.machine);
	S(name.domainname);

	I(ns.inum);

	return 0;
}

static void kernel_exit(void)
{
    printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
