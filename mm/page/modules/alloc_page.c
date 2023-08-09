/**
 *	File	alloc_page.c
 *	Time	2021.11.05
 *	Author	Rong Tao <rongtao@cestc.cn>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/mmdebug.h>
#include <linux/page_ref.h> //page_count()
#include <linux/page-flags.h> //PG_xxxx
#include <asm/pgtable.h>

/**
 *	Print page information
 */
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
	if(!page) {
		printk("fail alloc_page.\n");
	}
	__SetPageUptodate(page); //PG_uptodate 标志内容有效
	/* 设置页属性 */
	entry = mk_pte(page, PAGE_SHARED);
	entry = pte_sw_mkyoung(entry);//see do_anonymous_page()
	entry = pte_mkwrite(pte_mkdirty(entry)); //可写属性
	get_page(page); //_refcount++
	return page;
}

static void test__free(struct page *page)
{
	if(page) {
		put_page(page); //__refcount--
		__free_pages(page, 0);
	}
}


static int kernel_init(void)
{
#define npage 2
	int ipage;
	struct page *page[npage];

    printk(KERN_INFO "========== my init =========\n");
	for(ipage = 0; ipage < npage; ipage++) {
		page[ipage] = test__alloc();
		print_page(page[ipage]);
	}
	for(ipage = 0; ipage < npage; ipage++) {
		test__free(page[ipage]);
	}
    return 0;
}

static void kernel_exit(void)
{
	printk(KERN_INFO "my exit.\n");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
