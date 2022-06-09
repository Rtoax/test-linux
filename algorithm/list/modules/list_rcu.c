/**
 *   @file: rcu_list.c
 *
 *   @date: 2021.11.12
 *   @author: Rong Tao <rongtao@cestc.cn>
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/rculist.h>
#include <linux/slab.h>

LIST_HEAD(os_release_list);

struct os_release {
	struct list_head list;
	char release[20];
	char vender[20];
};

static struct os_release *alloc_os(const char *release, const char *vender)
{
	struct os_release *item;
	item = kmalloc(sizeof(struct os_release), GFP_KERNEL);
	strncpy(item->release, release, sizeof(item->release));
	strncpy(item->vender, vender, sizeof(item->vender));
	return item;
}

static void fill_list(void)
{
	const char* RELEASE[] = {"CentOS", "Ubuntu", "CCLinux", "OpenEuler"};
	const char* VENDERS[] = {"RedHat", "Canonical", "CESTC", "HuaWei"};

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

	rcu_read_lock();
	list_for_each_entry_rcu(entry, &os_release_list, list) {
		printk(KERN_INFO "%s - %s\n", entry->release, entry->vender);
	}
	rcu_read_unlock();
}

static void clean_list(void)
{
	struct os_release *entry;

	while (!list_empty(&os_release_list)) {
		entry = list_first_entry(&os_release_list, struct os_release, list);
		printk(KERN_INFO "freeing %s\n", entry->release);
		list_del_rcu(&entry->list);
		synchronize_rcu();
		kfree(entry);
	}
}

static int __init lkm_init(void)
{
	printk(KERN_INFO "Preparing RCU list module.\n");
	fill_list();
	print_list();
	return 0;
}

static void __exit lkm_cleanup(void)
{
	printk(KERN_INFO "Cleaning up rcu list module.\n\n");
	clean_list();
}

module_init(lkm_init);
module_exit(lkm_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A dynamic linux linked list example");
MODULE_VERSION("0.1");
