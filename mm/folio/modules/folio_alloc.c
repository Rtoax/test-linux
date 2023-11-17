#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/mmdebug.h>
#include <asm/pgtable.h>
#include <linux/page-flags.h>
#include <linux/cacheflush.h>
#include <linux/highmem.h>


static int order = 2;

static struct folio* test__alloc(void)
{
	struct folio *folio = folio_alloc(GFP_KERNEL | GFP_ATOMIC, order);
	if (!folio) {
		printk("fail folio_alloc.\n");
		return NULL;
	}
	printk("Folio size %ld\n", folio_size(folio));
	printk("Folio nr page %ld\n", folio_nr_pages(folio));
	folio_zero_range(folio, 0, folio_size(folio));
	flush_dcache_folio(folio);
	folio_mark_uptodate(folio);
	folio_get(folio);
	return folio;
}

static void test__free(struct folio *folio)
{
	if (folio) {
		int i, n = folio_nr_pages(folio);
		for (i = 0; i < n; i++)
			__free_pages(folio_page(folio, i), 0);
		folio_put(folio);
	}
}

static int kernel_init(void)
{
#define npage 2
	int i;
	struct folio *folio[npage];

	printk(KERN_INFO "========== my init =========\n");
	for (i = 0; i < npage; i++) {
		folio[i] = test__alloc();
	}
	for (i = 0; i < npage; i++) {
		test__free(folio[i]);
	}
	/* insmod failed on purpose */
	return -1;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
