// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2021-2025 Rong Tao */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/rwlock.h>

#define NR_KTHREAD 3

struct task_struct *task[NR_KTHREAD];

static unsigned long my_sum = 0;
static rwlock_t my_rwlock;

int thread_function(void *data)
{
	int nr_inc = 10000;

	while (!kthread_should_stop()) {

		if(nr_inc <= 0) {
			msleep_interruptible(1000);
			printk("kthread sleep.\n");
			continue;
		}

		write_lock(&my_rwlock);
		my_sum++;
		nr_inc--;
		if(!nr_inc) {
			write_unlock(&my_rwlock);
			continue;
		}
		write_unlock(&my_rwlock);

		schedule();
	}

	printk(KERN_INFO "thread done, sum = %ld\n", my_sum);
	return 0;
}

static int kernel_init(void)
{
	int itask;
	printk(KERN_INFO "mykthread init.\n");

	rwlock_init(&my_rwlock);

	for(itask = 0; itask < NR_KTHREAD; itask ++) {
		task[itask] = kthread_run(&thread_function, NULL, "rtoax-%d", itask);
	}

	return 0;
}

static void kernel_exit(void)
{
	int itask;
	for(itask = 0; itask < NR_KTHREAD; itask ++) {
		kthread_stop(task[itask]);
	}
	printk(KERN_INFO "Exit, SUM = %ld\n", my_sum);
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
