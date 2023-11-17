#include <linux/mm.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <asm/cacheflush.h>


static int __init flush_init(void);
static void __exit flush_exit(void);

void test_icache(void)
{
	unsigned long start = (unsigned long)flush_init;
	unsigned long end = (unsigned long)flush_exit;

	/* TODO: Flush icache */
	//__flush_icache_range(start, end);
}

void test_dcache(void)
{
	struct page *page = alloc_page(GFP_KERNEL|GFP_ATOMIC);
	if (!page) {
		printk(KERN_ERR "alloc_page failed.\n");
		return;
	}
	flush_dcache_page(page);
	__free_page(page);
}

static int __init flush_init(void)
{
	printk("flush_init.\n");

	test_icache();
	test_dcache();

	return -1;
}

static void __exit flush_exit(void)
{
	printk("flush_exit.\n");
}

module_init(flush_init);
module_exit(flush_exit);

MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
