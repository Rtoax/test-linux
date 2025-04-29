/**
 * ref: https://www.kernel.org/doc/html/latest/RCU/whatisRCU.html
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/completion.h>


static int async = 1;

module_param(async, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(async, "Use synchronize_rcu() if 0, use call_rcu if 1");


struct task_struct *tasks[4];

struct foo {
	int a;
	char b;
	long c;
	struct rcu_head rcu;
};
DEFINE_SPINLOCK(foo_mutex);

struct foo __rcu *gbl_foo;


static void foo_cleanup(int a) {}

/**
 * If the callback for call_rcu() is not doing anything more than calling
 * kfree() on the structure, you can use kfree_rcu() instead of call_rcu()
 * to avoid having to write your own callback.
 *
 * If the occasional sleep is permitted, the single-argument form may be
 * used, omitting the rcu_head structure from struct foo.
 *
 *	kfree_rcu_mightsleep(old_fp);
 */
static void foo_reclaim(struct rcu_head *rp)
{
	struct foo *fp = container_of(rp, struct foo, rcu);
	foo_cleanup(fp->a);
	kfree(fp);
}

/*
 * Create a new struct foo that is the same as the one currently
 * pointed to by gbl_foo, except that field "a" is replaced
 * with "new_a".  Points gbl_foo to the new structure, and
 * frees up the old structure after a grace period.
 *
 * Uses rcu_assign_pointer() to ensure that concurrent readers
 * see the initialized version of the new structure.
 *
 * Uses synchronize_rcu() to ensure that any readers that might
 * have references to the old structure complete before freeing
 * the old structure.
 *
 * Uses call_rcu() to ensure that any readers that might have
 * references to the old structure complete before freeing the
 * old structure.
 */
static void foo_update_a(int new_a)
{
	struct foo *new_fp;
	struct foo *old_fp;

	new_fp = kmalloc(sizeof(*new_fp), GFP_KERNEL);
	spin_lock(&foo_mutex);
	old_fp = rcu_dereference_protected(gbl_foo, lockdep_is_held(&foo_mutex));
	*new_fp = *old_fp;
	new_fp->a = new_a;
	rcu_assign_pointer(gbl_foo, new_fp);
	spin_unlock(&foo_mutex);

	if (likely(!async)) {
		/* Block and wait all read access done */
		synchronize_rcu();
		kfree(old_fp);
	} else {
		/* If it is not permitted to block, or only kfree_rcu() instead
		 * of call_rcu()
		 *
		 *	kfree_rcu(old_fp, rcu);
		 */
		call_rcu(&old_fp->rcu, foo_reclaim);
	}
}

/*
 * Return the value of field "a" of the current gbl_foo
 * structure.  Use rcu_read_lock() and rcu_read_unlock()
 * to ensure that the structure does not get deleted out
 * from under us, and use rcu_dereference() to ensure that
 * we see the initialized version of the structure (important
 * for DEC Alpha and for people reading the code).
 */
static int foo_get_a(void)
{
	int retval;

	rcu_read_lock();
	retval = rcu_dereference(gbl_foo)->a;
	rcu_read_unlock();
	return retval;
}

static int writer(void *data)
{
	int val = 0;

	while (!kthread_should_stop()) {
		foo_update_a(val++);

		msleep(400);
		schedule();
	}
	printk(KERN_INFO "Thread1: exit.\n");
	return 0;
}

static int reader(void *data)
{
	int old_val, val;

	old_val = val = -1;

	while (!kthread_should_stop()) {
		old_val = foo_get_a();
		if (val != old_val) {
			val = old_val;
			printk(KERN_INFO "RCU get %d\n", val);
		}
		msleep(400);
		schedule();
	}
	printk(KERN_INFO "Thread2: exit.\n");
	return 0;
}

static int kernel_init(void)
{
	gbl_foo = kmalloc(sizeof(*gbl_foo), GFP_KERNEL);
	gbl_foo->a = 1;

	tasks[0] = kthread_run(&writer, NULL, "rtoax-writer");
	tasks[1] = kthread_run(&reader, NULL, "rtoax-reader1");
	tasks[2] = kthread_run(&reader, NULL, "rtoax-reader2");
	tasks[3] = kthread_run(&reader, NULL, "rtoax-reader3");
	return 0;
}

static void kernel_exit(void)
{
	int i;

	for (i = 0; i < 4; i++)
		kthread_stop(tasks[i]);

	if (gbl_foo)
		kfree(gbl_foo);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
