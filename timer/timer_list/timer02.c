/**
 * [Question]  softlockup in run_timer_softirq
 *
 * insmod timer_test.ko size=1000 interval=100 dt=200
 *
 * ref: https://lore.kernel.org/lkml/fb8d80434b2148e78c0032c6c70a8b4d@huawei.com/
 */
#include <linux/module.h>
#include <linux/slab.h>
#include <asm-generic/delay.h>

static int stop = 1;

// timer num
static int size = 1000;
module_param(size, int, 0644);
MODULE_PARM_DESC(size, "size");

// Timeout of the timer
static int interval = 100;
module_param(interval, int, 0644);
MODULE_PARM_DESC(interval, "");

//elapsed time
static int dt = 200;
module_param(dt, int, 0644);
MODULE_PARM_DESC(dt, "");

struct wrapper {
	struct timer_list timer;
	spinlock_t lock;
};

struct wrapper *wr;

static void timer_func(struct timer_list *t)
{
	struct wrapper *w = from_timer(w, t, timer);

	spin_lock_bh(&(w->lock));
	if (stop == 0) {
		udelay(dt); // elapsed time
	}
	spin_unlock_bh(&(w->lock));

	if (stop == 0) {
		mod_timer(&(w->timer), jiffies + interval);
	}
}

static int __init maint_init(void)
{
	int i;

	wr = (struct wrapper *)kzalloc(size*sizeof(struct wrapper), GFP_KERNEL);

	for (i = 0; i < size; i++) {
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
	for (i = 0; i < size; i++) {
		struct wrapper *w = &wr[i];
		del_timer_sync(&(w->timer));
	}
	kfree(wr);

}

module_init(maint_init);
module_exit(maint_exit);
MODULE_LICENSE("GPL");
