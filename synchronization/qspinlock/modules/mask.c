#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm-generic/qspinlock.h>

#include "mask.h"


static int kernel_init(void)
{
#define Print(v32) \
	printk(KERN_INFO "%-32s : %#016x %32s\n", #v32, v32, binary32_unsafe(v32))

	printk(KERN_INFO "---------- print qspinlock val mask ---------\n");
	Print(_Q_LOCKED_MASK);
	Print(_Q_PENDING_MASK);
	Print(_Q_TAIL_IDX_MASK);
	Print(_Q_TAIL_CPU_MASK);
	Print(_Q_TAIL_MASK);

	/* insmod failed on purpose */
	return -1;
}

static void kernel_exit(void)
{
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
