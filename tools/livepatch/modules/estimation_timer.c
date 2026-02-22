#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/livepatch.h>
#include <linux/timer.h>
#include <linux/seq_file.h>
#include <linux/version.h>



#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 1, 0)
static void livepatch_estimation_timer(struct timer_list *t)
{
	return;
}
static struct klp_func funcs[] = {
	{
		.old_name = "estimation_timer",
		.new_func = livepatch_estimation_timer,
	}, { }
};
#else
static void livepatch_ip_vs_chain_estimation(struct hlist_head *chain)
{
	return;
}
static struct klp_func funcs[] = {
	{
		.old_name = "ip_vs_chain_estimation",
		.new_func = livepatch_ip_vs_chain_estimation,
	}, { }
};
#endif

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
	return klp_enable_patch(&patch);
}

static void livepatch_exit(void)
{
}

module_init(livepatch_init);
module_exit(livepatch_exit);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
