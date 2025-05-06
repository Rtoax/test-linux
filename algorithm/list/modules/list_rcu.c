#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/rculist.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include "os.h"


static spinlock_t list_lock;
static LIST_HEAD(os_release_list);

static struct os_release *alloc_os(const char *release, const char *vender)
{
	struct os_release *item;
	item = kmalloc(sizeof(struct os_release), GFP_KERNEL);
	strncpy(item->release, release, sizeof(item->release));
	strncpy(item->vender, vender, sizeof(item->vender));
	return item;
}

static void print_os(const char *prefix, struct os_release *entry)
{
	printk(KERN_INFO "%s %s %s\n", prefix ?: ">", entry->release, entry->vender);
}

static void fill_list(void)
{
	int i;
	struct os_release *item;
	for (i = 0; i < sizeof(RELEASE) / sizeof(RELEASE[0]); i++) {
		item = alloc_os(RELEASE[i], VENDERS[i]);
		list_add_tail(&item->list, &os_release_list);
	}
}

static void print_list(void)
{
	struct os_release *entry;

	printk(KERN_DEBUG "Print list:\n");
	rcu_read_lock();
	list_for_each_entry_rcu(entry, &os_release_list, list)
		print_os("Print:", entry);
	rcu_read_unlock();
}

static int delete_entry(const char *release)
{
	struct os_release *entry;

	spin_lock(&list_lock);
	list_for_each_entry(entry, &os_release_list, list) {
		if (!strcmp(entry->release, release)) {
			list_del_rcu(&entry->list);
			print_os("Delete: ", entry);
			spin_unlock(&list_lock);
			synchronize_rcu();
			kfree(entry);
			return 1;
		}
	}
	spin_unlock(&list_lock);
	return 0;
}

static void clean_list(void)
{
	struct os_release *entry;

	while (!list_empty(&os_release_list)) {
		entry = list_first_entry(&os_release_list, struct os_release, list);
		print_os("Clean: ", entry);
		list_del_rcu(&entry->list);
		synchronize_rcu();
		kfree(entry);
	}
}

static int __init lkm_init(void)
{
	printk(KERN_INFO "Preparing RCU list module.\n");

	spin_lock_init(&list_lock);

	fill_list();
	print_list();

	delete_entry(RELEASE[1]);
	print_list();
	return 0;
}

static void __exit lkm_cleanup(void)
{
	printk(KERN_INFO "Cleaning up rcu list module.\n\n");
	clean_list();
	print_list();
}

module_init(lkm_init);
module_exit(lkm_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A dynamic linux rcu linked list example");
MODULE_VERSION("0.2");
