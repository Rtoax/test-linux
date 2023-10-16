#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/completion.h>


#define NR_KTHREAD 1

struct task_struct *tasks[NR_KTHREAD];
static DECLARE_COMPLETION(cpu_running);


static int thread1(void *data)
{
	complete(&cpu_running);
	return 0;
}

static int kernel_init(void)
{
	int i;

	init_completion(&cpu_running);

	for (i = 0; i < NR_KTHREAD; i++) {
		tasks[i] = kthread_run(&thread1, NULL, "rtoax-%d", i);
	}

	wait_for_completion(&cpu_running);
	return 0;
}

static void kernel_exit(void)
{
	int i;

	complete_all(&cpu_running);

	for (i = 0; i < NR_KTHREAD; i++) {
		kthread_stop(tasks[i]);
	}
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
