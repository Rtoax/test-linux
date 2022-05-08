/**
 *	File	on_each_cpu.c
 *	Time	2021.11.03
 *	Author	Slava Imameev 
 *	Modify  Rong Tao <rongtao@cestc.cn>
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>   // for on_each_cpu

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");

void smp_call_func(void *info)
{
	/**
	 * a function is called with preemption disabled,
	 * so it is safe to call smp_processor_id()
	 */
	printk(KERN_INFO "Running on CPU[%i]\n", smp_processor_id());
	//__asm__ __volatile ("int $3\n");
}

static int __init each_cpu_init(void)
{
	printk(KERN_INFO "Hi from on_each_cpu!\n");

	on_each_cpu(smp_call_func, NULL, 2);

	return 0;
}

static void __exit each_cpu_exit(void)
{
	printk(KERN_INFO "Bye!\n");
}

module_init(each_cpu_init);
module_exit(each_cpu_exit);
