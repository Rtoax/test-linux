#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/kthread.h>
#include <linux/sched.h>

int local_i = 123;
int local_i_no;
/* No rela entry */
static int s_local_i = 123;

int global_int1;
int global_int2;
int global_int3 = 0xabcdffff;
static int sglobal_int1;

#define P_int(i)	printk(KERN_INFO "I: %-16s  %-8d %016lx.\n", #i, i, (unsigned long)&i);
#define P_long(l)	printk(KERN_INFO "L: %-16s  %-8lx %016lx.\n", #l, l, (unsigned long)&l);
#define P_f(f)		printk(KERN_INFO "F: %-16s           %016lx.\n", #f, (unsigned long)f);

void func1(void) {}
static void sfunc1(void)
{
	/* This is not RELA item. */
	kthread_run(NULL, NULL, NULL);
	schedule();
	printk("%d\n", global_int1);
}


void print(void) {}

static int kernel_init(void)
{
	local_i++;
	local_i_no += 1;
	s_local_i = 1234;

	printk("\n");
	P_int(local_i);
	P_int(local_i_no);
	P_int(s_local_i);
	P_f(kernel_init);
	P_f(print);
	P_f(schedule);
	P_f(wake_up_process);
	P_long(vmalloc_base);

	return -EINVAL;
}

module_init(kernel_init);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test ko ELF relocations");
