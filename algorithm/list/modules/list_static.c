#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>

LIST_HEAD(os_release_list);

struct os_release {
	struct list_head list;
	char *release;
	char *vender;
};

struct os_release c1 = {
	.release = "CentOS",
	.vender = "RedHat"
};

struct os_release c2 = {
	.release = "Ubuntu",
	.vender = "Canonical"
};

struct os_release c3 = {
	.release = "Fedora",
	.vender = "Redhat"
};

static void fill_list(void)
{
	list_add_tail(&c1.list, &os_release_list);
	list_add_tail(&c2.list, &os_release_list);
	list_add_tail(&c3.list, &os_release_list);
}

static void print_list(void)
{
	struct os_release *entry;

	list_for_each_entry(entry, &os_release_list, list) {
		printk(KERN_INFO "%s - %s\n", entry->release, entry->vender);
	}
}

static int __init hello_init(void)
{
	printk(KERN_INFO "Preparing linkedlist module.\n");
	fill_list();
	print_list();
	return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
	printk(KERN_INFO "Cleaning up linkedlist module.\n\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A linux statically allocated linked list example");
MODULE_VERSION("0.1");
