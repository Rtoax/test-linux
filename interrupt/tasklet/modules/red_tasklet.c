/*
 * Author: Zex <top_zlynch@yahoo.com>
 *
 * A Demo of tasklet&workqueue in the Linux kernel
 *
 * Copyright (c) by Zex Li <top_zlynch@yahoo.com>, Hytera Communications Co., Ltd.
 *
 * Sample command to load the module
 * 	insmod red_tasklet.ko user_name=Zex
 * 	insmod red_tasklet.ko user_name=Zex room_number=17
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h> // kmalloc
#include <linux/workqueue.h> // workqueue_struct
#include <linux/version.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zex");
MODULE_DESCRIPTION("Demo of tasklet in kernel");
MODULE_VERSION("0.0.1");

/* Referencing include/linux/moduleparam.h
 *
 * type of parameter: byte, short, ushort, int, uint, long,
 * ulong, charp, bool or invbool, or XXX if you define param_get_XXX,
 * param_set_XXX and param_check_XXX. */

static int room_number = 9381;
module_param(room_number, int, 0644);
MODULE_PARM_DESC(room_number,
	"room number (default: 9381)");

static char* greeting = "welcome!!";
module_param(greeting, charp, 0644);
MODULE_PARM_DESC(greeting, "simple greeting");

static char* user_name = "guest";
module_param(user_name, charp, 0644);
MODULE_PARM_DESC(user_name, "who to greeting");

static unsigned int delay_in_ms = 1500;
module_param(delay_in_ms, uint, 0644);
MODULE_PARM_DESC(delay_in_ms, "time to delay befor fire in ms");

char *red_tasklet_data = "The tasklet is red !!";

/**
 * https://elixir.bootlin.com/linux/v5.9/source/include/linux/interrupt.h
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)
static void tasklet_callback(struct tasklet_struct *data)
#else
static void tasklet_callback(unsigned long int data)
#endif
{
	printk( "%s\n", red_tasklet_data );
	room_number -= 100;
	printk( "%d\n", room_number );
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)
DECLARE_TASKLET( red_tasklet, tasklet_callback);
#else
DECLARE_TASKLET( red_tasklet, tasklet_callback, 0);
#endif

static struct workqueue_struct *wq_a;

typedef struct {
	struct work_struct work;
	int number;
	char prefix;
} WorkType;

WorkType *wk1, *wk2;

static void job_a( struct work_struct *work )
{
	WorkType *wk = (WorkType*)work;

	printk( "wk->number %d\n", wk->number );
	kfree( (void*)work );
}

static void create_work_queue(void)
{
	int ret;
	wq_a = create_workqueue( "workqueueA" );

	if ( !wq_a ) {
		printk( "create workqueue failed\n" );
		return ;
	}

	wk1 = (WorkType*)kmalloc( sizeof(WorkType), GFP_KERNEL );
	wk2 = (WorkType*)kmalloc( sizeof(WorkType), GFP_KERNEL );

	if ( wk1 ) {
		INIT_WORK( &wk1->work, job_a );
		wk1->number = 31;
		ret = queue_work( wq_a, &wk1->work );
	}

	if ( wk2 ) {
		INIT_WORK( &wk2->work, job_a );
		wk2->number = 991;
		ret = queue_work( wq_a, &wk2->work );
	}

}

static int red_init(void)
{
	printk(KERN_INFO "Hello.");
	red_tasklet.data = (unsigned long)red_tasklet_data;
	create_work_queue();
	tasklet_schedule( &red_tasklet );
	tasklet_hi_schedule( &red_tasklet );
//	schedule_on_each_cpu(job_a);
//	schedule_work( wk1->work );
//	schedule_work( wk2->work );
	return 0;
}

static void cleanup(void)
{
	printk(KERN_INFO "Bye.");
	tasklet_kill( &red_tasklet );
	flush_workqueue( wq_a );
	destroy_workqueue( wq_a );
}

module_init(red_init);
module_exit(cleanup);
