/**
 * [Question]  softlockup in run_timer_softirq
 *
 * insmod timer_test.ko nr=1000 interval=100 dt=200
 *
 * ref: https://lore.kernel.org/lkml/fb8d80434b2148e78c0032c6c70a8b4d@huawei.com/
 * ref: https://blog.csdn.net/dog250/article/details/104997385
 */
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <asm-generic/delay.h>

static int stop = 1;

/* number of timer */
static int nr = 1000;
module_param(nr, int, 0644);
MODULE_PARM_DESC(nr, "Number of timers");

/* timer's interval */
static int interval = 100;
module_param(interval, int, 0644);
MODULE_PARM_DESC(interval, "Interval of timer");

/* elapsed time */
static int dt = 200;
module_param(dt, int, 0644);
MODULE_PARM_DESC(dt, "Timer's callback occupy");

struct wrapper {
	struct timer_list timer;
	spinlock_t lock;
};

struct wrapper *wr;

/**
 * Timer callback in softirq, it's can't be preempted by any task. If all the
 * timer's callbacks spent time bigger than 20s(watchdog), soft lockup will
 * happen.
 */
static void timer_func(struct timer_list *t)
{
/**
 * linux v6.15-13744-g41cb08555c41
 * commit 41cb08555c41 ("treewide, timers: Rename from_timer() to timer_container_of()")
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
	struct wrapper *w = timer_container_of(w, t, timer);
#else
	struct wrapper *w = from_timer(w, t, timer);
#endif

	spin_lock_bh(&(w->lock));
	if (stop == 0) {
		/* i'm busy */
		udelay(dt);
	}
	spin_unlock_bh(&(w->lock));

	if (stop == 0) {
		mod_timer(&(w->timer), jiffies + interval);
	}
}

static int __init maint_init(void)
{
	int i;

	wr = (struct wrapper *)kzalloc(nr * sizeof(struct wrapper), GFP_KERNEL);

	for (i = 0; i < nr; i++) {
		struct wrapper *w = &wr[i];
		spin_lock_init(&(w->lock));
		timer_setup(&(w->timer), timer_func, 0);
		mod_timer(&(w->timer), jiffies + 20);
	}
	stop = 0;

	return 0;
}

static void __exit maint_exit(void)
{
	int i;

	stop = 1;
	udelay(100);
	for (i = 0; i < nr; i++) {
		struct wrapper *w = &wr[i];
/**
 * linux v6.14-13424-g8fa7292fee5c
 * commit 8fa7292fee5c ("treewide: Switch/rename to timer_delete[_sync]()")
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 14, 0)
		timer_delete_sync(&w->timer);
#else
		del_timer_sync(&w->timer);
#endif
	}
	kfree(wr);
}

module_init(maint_init);
module_exit(maint_exit);
MODULE_LICENSE("GPL");
