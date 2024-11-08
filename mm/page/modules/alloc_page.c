#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/gfp.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <linux/mmdebug.h>
#include <linux/page_ref.h> //page_count()
#include <linux/page-flags.h> //PG_xxxx
#include <asm/pgtable.h>
#include <linux/pgtable.h>


static void print_page(struct page* page)
{
	printk("flags     %lx\n", page->flags);
	printk("pageAddr  %p\n", page_address(page));
	printk("_mapcount %d\n", page_mapcount(page));
	printk("_refcount %d\n", page_count(page));
	printk("PageAnon  %d\n", PageAnon(page));
	printk("page2virt %p\n", page_to_virt(page));
	printk("page2pfn  %lx\n", page_to_pfn(page));
	dump_page(page, "I just wanna see page.");
}

static struct page* test__alloc(void)
{
	pte_t entry;
	struct page *page = alloc_page(GFP_KERNEL|GFP_ATOMIC);
	if (!page) {
		printk("fail alloc_page.\n");
		return NULL;
	}
	/* PG_uptodate 标志内容有效 */
	__SetPageUptodate(page);
	/* 设置页属性 */
	entry = mk_pte(page, PAGE_SHARED);
	entry = pte_sw_mkyoung(entry);
/**
 * commit 161e393c0f63 ("mm: Make pte_mkwrite() take a VMA")
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0)
	/* 可写属性 */
	entry = pte_mkwrite(pte_mkdirty(entry));
#endif
	/* __refcount++ */
	get_page(page);
	return page;
}

static void test__free(struct page *page)
{
	if (page) {
		/* __refcount-- */
		put_page(page);
		__free_pages(page, 0);
	}
}

static int kernel_init(void)
{
#define npage 2
	int ipage;
	struct page *page[npage];

	printk(KERN_INFO "========== my init =========\n");
	for (ipage = 0; ipage < npage; ipage++) {
		page[ipage] = test__alloc();
		print_page(page[ipage]);
	}
	for (ipage = 0; ipage < npage; ipage++) {
		test__free(page[ipage]);
	}
	/* insmod failed on purpose */
	return -1;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
