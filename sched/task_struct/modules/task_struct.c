#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>

static int __init print_task_struct(void)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
# define Sfmt "%x"
# define STATE __state
#else
# define Sfmt "%lx"
# define STATE state
#endif
	printk("Offset state = %ld\n", offsetof(struct task_struct, STATE));
	printk("Offset flags = %ld\n", offsetof(struct task_struct, flags));
	printk("Offset comm = %ld\n", offsetof(struct task_struct, comm));
	printk("Offset se.on_rq = %ld\n", offsetof(struct task_struct, se.on_rq));
	return 0;
}

static void __exit print_exit(void)
{
	printk("exiting...\n");
}

module_init(print_task_struct);
module_exit(print_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
