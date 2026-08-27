#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/printk.h>
#include <linux/slab.h>
/**
 * linux v6.7-rc1-9-g16a1d968358a
 * commit 16a1d968358a ("mm/slab: remove mm/slab.c and slab_def.h")
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 7, 0)
#include <linux/slab_def.h>
#endif
#include <linux/gfp.h>
#include "kasan.h"

struct test_struct {
	int id;
	int ip;
	char name[500];
};

#define SLAB_NAME	"rtoax"
#define SLAB_ELEM	32
static struct kmem_cache *test_slab;
static int count_ctor = 0;

void test_constructor(void *data)
{
	struct test_struct *test = (struct test_struct*)data;
	test->id = 1;
	count_ctor++;
}

void print_kmem_cache(struct kmem_cache *cache)
{
	printk("%-5s %-5s %-8s %-4s\n", "NUM", "SIZE", "OBJSIZE", "REF");
	printk("%-5d %-5d %-8d %-4d\n", test_slab->num, test_slab->size,
	       test_slab->object_size, test_slab->refcount);
}

static int create_slab(void)
{
	test_slab = kmem_cache_create(SLAB_NAME, sizeof(struct test_struct), 0,
				      SLAB_PANIC, test_constructor);
	if (!test_slab) {
		pr_err("Create slab fail.\n");
		return -1;
	}
	return 0;
}

static void test__slab(void)
{
	int i;
	char *datas[SLAB_ELEM] = {NULL};
	struct test_struct *test;

	if (!test_slab) {
		pr_warn("not test.\n");
		return;
	}

	for (i = 0; i < SLAB_ELEM; i++) {
		datas[i] = kmem_cache_alloc(test_slab, GFP_KERNEL);
	}

	print_kmem_cache(test_slab);

	test = (struct test_struct *)datas[0];
	/**
	 * 越界访问, 但是 dmesg 看不到出错警告.
	 */
	test[2].id = 1;

	for (i = 0; i < SLAB_ELEM; i++) {
		kmem_cache_free(test_slab, datas[i]);
		datas[i] = NULL;
	}
	return;
}

static void destroy_slab(void)
{
	if (test_slab) {
		kmem_cache_destroy(test_slab);
	}
}

static int kernel_init(void)
{
	printk(KERN_INFO "my init.\n");
	create_slab();
	test__slab();

	printk("count_ctor = %d\n", count_ctor);
	return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
	destroy_slab();
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
