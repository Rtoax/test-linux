#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include "os.h"


static LIST_HEAD(os_release_list);

static void fill_list(void)
{
	list_add_tail(&centos.list, &os_release_list);
	list_add_tail(&ubuntu.list, &os_release_list);
	list_add_tail(&fedora.list, &os_release_list);
}

static void print_list(void)
{
	struct os_release *entry;
	list_for_each_entry(entry, &os_release_list, list)
		printk(KERN_INFO "%s - %s\n", entry->release, entry->vender);
}

static int __init hello_init(void)
{
	printk(KERN_INFO "Preparing linkedlist module.\n");
	fill_list();
	print_list();
	return -EINVAL;
}

module_init(hello_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A linux statically allocated linked list example");
MODULE_VERSION("0.2");
