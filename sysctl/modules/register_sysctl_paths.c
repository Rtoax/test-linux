/**
 *	File register_sysctl_paths.c
 *	Time 2021.11.17
 *	Author	Rong Tao <rtoax@foxmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysctl.h>

#define SYSCTL_ENTRY(name, pint)		\
		{						\
			.procname	= name,			\
			.data		= pint,	\
			.maxlen		= sizeof(int),		\
			.mode		= 0644,			\
			.proc_handler	= proc_dointvec,	\
			.extra1		= SYSCTL_ZERO,		\
			.extra2		= SYSCTL_INT_MAX,	\
		}

static int rt1 = 100;

const struct ctl_path kernel_path = {
	.procname = "kernel",
};
struct ctl_table_header *rongtao_header;
struct ctl_table rongtao = SYSCTL_ENTRY("rt1", &rt1);

static int __init my_init(void)
{
	printk("my module is working..\n");
	printk("check /proc/sys/kernel/rt1 \n");
	
	rongtao_header = register_sysctl_paths(&kernel_path, &rongtao);

	return 0;
}

static void __exit my_exit(void)
{
	printk("my module is leaving..\n");

	if(rongtao_header) {
		unregister_sysctl_table(rongtao_header);
	}
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
