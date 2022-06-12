/**
 * File show_softirqs.c
 * Time 2021.11.15
 * Author Rong Tao <rongtao@cestc.cn>
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Rong Tao");

const char * const softirq_to_name[NR_SOFTIRQS] = {
	"HI",       /* 高优先级 */
	"TIMER",    /* 定时器 */
	"NET_TX",   /* 网络发包 */
	"NET_RX",   /* 网络收包 */
	"BLOCK",    /* 块 */
	"IRQ_POLL", /* 中断 poll */
	"TASKLET",  /* 小任务 tasklet */
	"SCHED",    /* 调度 */
	"HRTIMER",  /* 高精度定时器 */
	"RCU"       /* Read Copy Update */
};

static int show_softirqs(struct seq_file *p, void *v)
{
	int i, j;

	seq_puts(p, "Rong Tao /proc/softirqs-rongtao\n");
	seq_puts(p, "         ");
	for_each_possible_cpu(i){
		seq_printf(p, "CPU%-7d", i);}
	seq_putc(p, '\n');

	for (i = 0; i < NR_SOFTIRQS; i++) {
		seq_printf(p, "%9s:", softirq_to_name[i]);
		for_each_possible_cpu(j) {
			seq_printf(p, " %7u", kstat_softirqs_cpu(i, j));}
		seq_putc(p, '\n');
	}
	return 0;
}
struct proc_dir_entry *proc_softirqs;

static int hello_init(void)
{
	printk(KERN_ALERT "init: NR_SOFTIRQS is %d\n", NR_SOFTIRQS);
	proc_softirqs = proc_create_single("softirqs-rongtao", 
						0, NULL, show_softirqs);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "exit: Goodbye, crash world\n");
	proc_remove(proc_softirqs);
}

module_init(hello_init);
module_exit(hello_exit);
