#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/printk.h>

int global_int1;
int global_int2;
int global_int3 = 0xabcdffff;
static int sglobal_int1;

void func1(void) {}
static void sfunc1(void)
{
	/* This is not RELA item. */
	kthread_run(NULL, NULL, NULL);
	printk("%d\n", global_int1);
}

MODULE_LICENSE("Dual BSD/GPL");
