#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include "os.h"

static LIST_HEAD(os_release_list);

static void fill_list(void)
{
	int i;
	struct os_release *item;

	for (i = 0; i < sizeof(RELEASE) / sizeof(RELEASE[0]); i++) {
		item = kmalloc(sizeof(struct os_release), GFP_KERNEL);
		strncpy(item->release, RELEASE[i], sizeof(item->release));
		strncpy(item->vender, VENDERS[i], sizeof(item->vender));
		list_add_tail(&item->list, &os_release_list);
	}
}

static void print_list(void)
{
	struct os_release *entry;

	list_for_each_entry(entry, &os_release_list, list) {
		printk(KERN_INFO "%s - %s\n", entry->release, entry->vender);
	}
}

static void clean_list(void)
{
	struct os_release *entry;

	while (!list_empty(&os_release_list)) {
		entry = list_first_entry(&os_release_list, struct os_release, list);
		printk(KERN_INFO "freeing %s\n", entry->release);
		list_del(&entry->list);
		kfree(entry);
	}
}

static int __init lkm_init(void)
{
	printk(KERN_INFO "Preparing dynamiclinkedlist module.\n");
	fill_list();
	print_list();
	return 0;
}

static void __exit lkm_cleanup(void)
{
	printk(KERN_INFO "Cleaning up dynamiclinkedlist module.\n\n");
	clean_list();
}

module_init(lkm_init);
module_exit(lkm_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A dynamic linux linked list example");
MODULE_VERSION("0.2");
