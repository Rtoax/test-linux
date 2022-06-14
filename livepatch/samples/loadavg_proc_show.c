#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/livepatch.h>
#include <linux/sched.h>
#include <linux/sched/loadavg.h>
#include <linux/sched/stat.h>
#include <linux/pid_namespace.h>
#include <linux/proc_fs.h>

#include <linux/seq_file.h>

#define LOAD_INT(x) ((x) >> FSHIFT)
#define LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1-1)) * 100)

static int livepatch_loadavg_proc_show(struct seq_file *m, void *v) 
{
	unsigned long __attribute__((unused)) avnrun[3];
	seq_printf(m, "RongTao: \n");
	return 0;
}

static struct klp_func funcs[] = {
	{
		.old_name = "loadavg_proc_show",
		.new_func = livepatch_loadavg_proc_show,
	}, { }
};

static struct klp_object objs[] = {
	{
		/* name being NULL means vmlinux */
		.funcs = funcs,
	}, { }
};

static struct klp_patch patch = {
	.mod = THIS_MODULE,
	.objs = objs,
};

static int livepatch_init(void)
{
	int ret;

	ret = klp_enable_patch(&patch);
	if (ret) {
		return ret;
	}
	printk(KERN_INFO "livepatch insert.");
	return 0;
}

static void livepatch_exit(void)
{
	printk(KERN_INFO "livepatch exit.");
}

module_init(livepatch_init);
module_exit(livepatch_exit);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
