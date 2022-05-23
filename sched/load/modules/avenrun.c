/**
 * File: avenrun.c
 * Author: Rong Tao <rongtao@cestc.cn>
 * Date: 2022.05.23
 *
 * Print load average like 'uptime' and bpftrace/tools loads.bt.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/pid_namespace.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/loadavg.h>
#include <linux/sched/stat.h>
#include <linux/seq_file.h>
#include <linux/seqlock.h>
#include <linux/time.h>

/**
 * see kernel/sched/loadavg.c
 */
void get_avenrun(unsigned long *loads, unsigned long offset, int shift)
{
    loads[0] = (avenrun[0] + offset) << shift;
    loads[1] = (avenrun[1] + offset) << shift;
    loads[2] = (avenrun[2] + offset) << shift;
}

/**
 * $ sudo cat /proc/loadavg
 *   0.00 0.02 0.05 1/275 96511
 */
static int loadavg_proc_show(void)
{
	unsigned long avnrun[3];

	get_avenrun(avnrun, FIXED_1/200, 0);

	printk("%lu.%02lu %lu.%02lu %lu.%02lu\n",
		LOAD_INT(avnrun[0]), LOAD_FRAC(avnrun[0]),
		LOAD_INT(avnrun[1]), LOAD_FRAC(avnrun[1]),
		LOAD_INT(avnrun[2]), LOAD_FRAC(avnrun[2]));
	return 0;
}

static int __init avenrun_init(void)
{
	loadavg_proc_show();
	return 0;
}

static void __exit avenrun_exit(void)
{
	printk("exiting...\n");
}

module_init(avenrun_init);
module_exit(avenrun_exit);
MODULE_LICENSE("GPL");
