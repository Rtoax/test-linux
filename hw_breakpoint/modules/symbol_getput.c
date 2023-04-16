// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * symbol-put.c - test __symbol_get() - symbol_put()
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/kallsyms.h>

#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>

static char ksym_name[KSYM_NAME_LEN] = "jiffies";

static int __init s_module_init(void)
{
	void *addr = __symbol_get(ksym_name);

	if (!addr)
		return -ENXIO;

	printk(KERN_INFO "__symbol_get(%s) success\n", ksym_name);

	return 0;
}

static void __exit s_module_exit(void)
{
	symbol_put(ksym_name);
	printk(KERN_INFO "symbol_put(%s) success\n", ksym_name);
}

module_init(s_module_init);
module_exit(s_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("test symbol get/put");
