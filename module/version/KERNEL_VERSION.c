#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/utsname.h>
#include <linux/version.h>
#ifndef INCLUDE_VERMAGIC
#define INCLUDE_VERMAGIC
#endif
#include <linux/vermagic.h>


static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");
#define	S(v) printk(KERN_INFO "init_uts_ns.%s = %s\n", #v, init_uts_ns.v)
#define	I(v) printk(KERN_INFO "init_uts_ns.%s = %d\n", #v, init_uts_ns.v)

	/**
	 * Don't have kref since >= 5.11
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

#ifdef LINUX_VERSION_MAJOR
	printk("Version: %d.%d.%d\n", LINUX_VERSION_MAJOR,
		LINUX_VERSION_PATCHLEVEL, LINUX_VERSION_SUBLEVEL);
#endif

#ifdef VERMAGIC_STRING
	printk("Vermagic %s\n", VERMAGIC_STRING);
#else
#pragma message "Not found macro VERMAGIC_STRING"
#endif

	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
