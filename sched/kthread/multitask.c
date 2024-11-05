#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/spinlock_types.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/kallsyms.h>
#include <linux/version.h>

#define NTHREADS 200

struct my_struct {
	struct list_head list;
	int id;
	int pid;
};

static struct work_struct work_queue;
static struct timer_list mytimer;
static LIST_HEAD(tasks_list);
static unsigned int list_len = 0;
/**
 * kernel commit 48380368dec1 ("Change DEFINE_SEMAPHORE() to take a number
 * argument") add number argument.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0)
static DEFINE_SEMAPHORE(sem, 0);
#else
static DEFINE_SEMAPHORE(sem);
#endif
static DEFINE_SPINLOCK(my_lock);
static atomic_t my_count = ATOMIC_INIT(0);
static int count = 0;

static int sharelist_fn(void *data);
static void start_kthread(void);
static void kthread_launcher(struct work_struct *q);


static int sharelist_fn(void *data)
{
	int err = 0;
	struct my_struct *p;

	if (count++ % 4 == 0)
		printk("\n");

	spin_lock(&my_lock);

	if (list_len < 50) {
		p = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
		if (p  == NULL) {
			err = -ENOMEM;
			goto unlock;
		}
		p->id = atomic_read(&my_count);
		p->pid = current->pid;
		list_add(&p->list, &tasks_list);
		atomic_inc(&my_count);
		list_len++;
		printk("THREAD ADD:%-5d\t", p->id);
	} else {
		struct my_struct *my;
		my = list_entry(tasks_list.prev, struct my_struct, list);
		list_del(tasks_list.prev);
		atomic_dec(&my_count);
		list_len--;
		printk("THREAD DEL:%-5d\t", my->id);
		kfree(my);
	}

unlock:
	spin_unlock(&my_lock);
	return 0;
}

static void start_kthread(void)
{
	down(&sem);
	schedule_work(&work_queue);
}

static void kthread_launcher(struct work_struct *q)
{
	kthread_run(sharelist_fn, NULL, "kthread-%d", count);
	up(&sem);
}

void timer_callback(struct timer_list *timer)
{
	spin_lock(&my_lock);
	if (!list_empty(&tasks_list)) {
		struct my_struct *i;
		if (count++ % 4 == 0)
			printk("\n");
		i = list_entry(tasks_list.next, struct my_struct, list);
		list_del(tasks_list.next);
		list_len--;
		printk("TIMER DEL:%-5d\t", i->id);
		kfree(i);
	}
	spin_unlock(&my_lock);
	mod_timer(timer, jiffies + msecs_to_jiffies(1000));
}

static __init int share_init(void)
{
	int i;
	printk(KERN_INFO"share list enter\n");

	INIT_WORK(&work_queue, kthread_launcher);

	timer_setup(&mytimer, timer_callback, 0);
	add_timer(&mytimer);

	for (i = 0; i < NTHREADS; i++)
		start_kthread();
	return 0;
}

static __exit void share_exit(void)
{
	struct list_head *n, *p = NULL;
	struct my_struct *my = NULL;

	printk("\nshare list exit\n");

	del_timer(&mytimer);

	spin_lock(&my_lock);

	list_for_each_safe(p, n, &tasks_list) {
		if (count++ % 4 == 0)
			printk("\n");
		my = list_entry(p, struct my_struct, list);
		list_del(p);
		printk("SYSCALL DEL: %d\t", my->id);
		kfree(my);
	}

	spin_unlock(&my_lock);

	printk(KERN_INFO"Over \n");
}

module_init(share_init);
module_exit(share_exit);

MODULE_LICENSE("GPL v2");
