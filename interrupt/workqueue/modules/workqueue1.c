#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/workqueue.h>

static int sleep = 0;

struct work_data {
	struct work_struct my_work;
	wait_queue_head_t my_waitqueue;
	int struct_data;
};

static void work_handler(struct work_struct *work)
{
	struct work_data *this_data = container_of(work, struct work_data, my_work);
	printk("Work queue module handler %s, data is %d\n", __FUNCTION__, this_data->struct_data);
	msleep(2000);
	/* comment sleep = 1 to wait indefinitely until ctrl+c interrupts*/
	sleep = 1;
	wake_up_interruptible(&this_data->my_waitqueue);
	kfree(this_data);
}

static int __init onload(void)
{
	struct work_data *my_data;

	my_data = kmalloc(sizeof(struct work_data), GFP_KERNEL);
	my_data->struct_data = 42;

	INIT_WORK(&my_data->my_work, work_handler);
	init_waitqueue_head(&my_data->my_waitqueue);

	schedule_work(&my_data->my_work);
	printk("Going to sleep...\n");
	wait_event_interruptible(my_data->my_waitqueue, sleep != 0);
	printk("I have awoken...\n");
	return 0;
}

static void __exit onunload(void)
{
	printk("Work queue module exit: %s %d\n", __FUNCTION__, __LINE__);
}

module_init(onload);
module_exit(onunload);
MODULE_AUTHOR("Liam Ryan <liamryandev@gmail.com>");
MODULE_LICENSE("GPL");
