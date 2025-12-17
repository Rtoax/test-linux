#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>   // for on_each_cpu

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

	/* I don't want to rmmod */
	return -EINVAL;
}

module_init(each_cpu_init);
MODULE_AUTHOR("Slava Imameev & Rong Tao");
MODULE_LICENSE("GPL");
