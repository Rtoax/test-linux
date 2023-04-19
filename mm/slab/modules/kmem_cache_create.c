/**
 *	File	slab.c
 *	Time	2021.11.05
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/gfp.h>

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
	/**
	 * kernel slab_def.h introduce new slab_address(), we can't print kmem_cache
	 * in module anymore.
	 */
#if 0
	printk("%-5d %-5d %-8d %-4d\n",
			test_slab->num,
			test_slab->size,
			test_slab->object_size,
			test_slab->refcount);
#endif
}

static int create_slab(void)
{
	test_slab = kmem_cache_create(SLAB_NAME,
				sizeof(struct test_struct),
				0,
				SLAB_PANIC,
				test_constructor);
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

	if (!test_slab) {
		pr_warn("not test.\n");
		return;
	}

	for (i = 0; i < SLAB_ELEM; i++) {
		datas[i] = kmem_cache_alloc(test_slab, GFP_KERNEL);
	}

	print_kmem_cache(test_slab);

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
