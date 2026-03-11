#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h> 
#include <linux/version.h>

char tasklet_data[] = "Using a string but it could easily be struct pointer\n";

/* Tasklet handler, just prints data held in the tasklet */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)
void tasklet_work(struct tasklet_struct *tasklet)
{
	printk("%s\n", (char *) tasklet->data);
}
#else
void tasklet_work(unsigned long int data)
{
	printk("%s\n", (char *) data);
}
#endif

/**
 * https://elixir.bootlin.com/linux/v5.9/source/include/linux/interrupt.h
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)
DECLARE_TASKLET(my_tasklet, tasklet_work);
#else
DECLARE_TASKLET(my_tasklet, tasklet_work, 0);
#endif

static int __init onload(void)
{
	my_tasklet.data = (unsigned long)tasklet_data;
	tasklet_schedule(&my_tasklet);
	return 0;
}

static void onunload(void)
{
	tasklet_kill(&my_tasklet);
}

module_init(onload);
module_exit(onunload);
MODULE_AUTHOR("Liam Ryan <liamryandev@gmail.com>");
MODULE_LICENSE("GPL");
