/**
 *	
 *	Reference
 *	https://medium.com/geekculture/the-linux-kernel-locking-api-and-shared-objects-1169c2ae88ff
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

static DECLARE_WAIT_QUEUE_HEAD(my_wq);
static int condition = 0;

/* declare a work queue*/
static struct work_struct wrk;

/**
 *	当前进程（实际上，这是 insmod）将在等待队列中
 *	休眠 5 秒并被工作处理程序唤醒
 */
static void work_handler(struct work_struct *work)
{
	pr_info("Waitqueue module handler %s\n", __FUNCTION__);
	msleep(5000);
	pr_info("Wake up the sleeping module\n");
	condition = 1;
	wake_up_interruptible(&my_wq);
}

static int __init my_init(void)
{
	pr_info("Wait queue example\n");
	INIT_WORK(&wrk, work_handler);
	schedule_work(&wrk);
	pr_info("Going to sleep %s\n", __FUNCTION__);
	/**
	 *	如果没有检查 wait_event_interruptible() 的返回值。
	 *	有时（如果不是大部分时间），这可能会导致严重的问题
	 */
	if(wait_event_interruptible(my_wq, condition != 0)) {
		pr_info("Catch a crash signal.\n"); 
		/* 处理这种情况，不访问数据 */ 
	} else { 
		/* 访问数据并处理它 */
	}
	pr_info("woken up by the work job\n");
	return 0;
}

void my_exit(void)
{
	pr_info("waitqueue example cleanup\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("John Madieu <john.madieu@labcsmart.com>");
MODULE_LICENSE("GPL");
