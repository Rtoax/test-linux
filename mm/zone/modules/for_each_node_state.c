/**
 *	File	for_each_node_state.c
 *	Time	2021.11.10
 *	Author	Rong Tao <rtoax@foxmail.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/mmzone.h>

static int kernel_init(void)
{
	int node;
	enum node_states state = N_ONLINE;

    printk(KERN_INFO "my init.\n");

	for_each_node_state(node, state) {
		printk(KERN_INFO "node %d, state %d\n", node, state);
	}

    return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
