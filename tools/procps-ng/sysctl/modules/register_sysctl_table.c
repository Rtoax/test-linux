/**
 *	File register_sysctl_table.c
 *	Time 2021.11.17
 *	Author	Rong Tao <rtoax@foxmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysctl.h>

struct ctl_table_header *table_hdr;

unsigned int rt1 = 100;
unsigned int rt2 = 200;

static struct ctl_table rongtao_table[] = {
	{
		/* /proc/sys/rongtao/rt1 */
		.procname = "rt1",
		.data = &rt1,
		.maxlen = sizeof(unsigned int),
		.mode = 0644,
		.proc_handler = proc_dointvec
	},
	{
		/* /proc/sys/rongtao/rt2 */
		.procname = "rt2",
		.data = &rt2,
		.maxlen = sizeof(unsigned int),
		.mode = 0644,
		.proc_handler = proc_dointvec
	},
	{}
};

static struct ctl_table sysctl_rongtao_table[] = {
	{
		/* /proc/sys/rongtao/ */
		.procname = "rongtao",
		.mode = 0755,
		.child = rongtao_table,
	},
	{ }
};

static int __init my_init(void)
{
	printk("my module is working..\n");
	printk("check in /proc/sys/rongtao/\n");

	table_hdr = register_sysctl_table(sysctl_rongtao_table);

	return 0;
}

static void __exit my_exit(void)
{
	printk("my module is leaving..\n");
	unregister_sysctl_table(table_hdr);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
